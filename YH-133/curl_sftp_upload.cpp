#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

#include <libssh/libssh.h>
#include <libssh/libsshpp.hpp>

static size_t WriteCallback(void *in_data, size_t size, size_t nmemb, void *out_data)
{
    size_t realsize = size * nmemb;
    ((std::string*)out_data)->append((char*)in_data, realsize);
    return realsize;
}

static size_t readCallback(void *in_ptr, size_t size, size_t nmemb, void *file_name)
{
    size_t   rc;
    FILE *fp = fopen((char*)file_name, "rb");
    if ( in_ptr == nullptr ) {
        std::cout << "CURLOPT_READFUNCTION readCallback failed (in_ptr is nullptr)" << std::endl;
        return 0;
    }
    rc = fread(in_ptr, size, nmemb, fp);
    fclose(fp);
    return rc;
}

long get_file_size(char *filename) {
    FILE *fp = fopen(filename, "rb");

    if (fp==NULL)
        return -1;

    if (fseek(fp, 0, SEEK_END) < 0) {
        fclose(fp);
        return -1;
    }

    long size = ftell(fp);
    // release the resources when not required
    fclose(fp);
    return size;
}

int main(int argc, char* argv[])
{
    CURL *curl;
    std::string recvBuffer;
    std::ifstream in_file;

   /*
    * To execute SFTP upload it requires <server IP>, <login ID>, <password>, <from file> and [to file]
    * From file is local to file is on server
    * usage will have 4 arguments
    * password will be securely keyed in from screen
    */

    if (argc < 4 )
    {
        std::cout << "Usage: " << argv[0] << " <url> <login name> <From File> [To File]" << std::endl;
        std::cout << "Example : " << std::endl;
        std::cout << argv[0] << " 192.168.0.107 hyuan my_text.txt" << std::endl;
        std::cout << argv[0] << " 192.168.0.107 hyuan my_text.txt /tmp/my_text.txt" << std::endl;
        return (EXIT_FAILURE);
    }


    /*
     *   libcurl url format : sftp://username:passwd@server_ip/path/to_filename
     */

    char      my_PassWd[30];
    memset(my_PassWd, '\0', sizeof(my_PassWd));
    int ret = ssh_getpass("Password : ", my_PassWd, sizeof(my_PassWd), 0, 0);
    if ( ret != 0 ) {
        std::cout << "Error Password : " << ret << std::endl;
        return (EXIT_FAILURE);
    }

    /*
     *  before SFTP it requires to get uploading file size
     */

    long file_size = get_file_size(argv[3]);
    if ( file_size <= 0 ) {
        std::cout << "Empty File : " << file_size << std::endl;
        return (EXIT_FAILURE);
    }

    std::string url_string = "sftp://" + std::string(argv[2]) + ":" + my_PassWd + "@" + std::string(argv[1]);
    if ( argc == 5 )
        url_string += std::string(argv[4]);
    else
        url_string += std::string(argv[3]);

    curl_global_init(CURL_GLOBAL_ALL); // <-- Global libcurl initialization
    curl = curl_easy_init();           // <-- init easy interface and get a handle
    if(curl) {

        /*
         *  1) set url and default protcol : CURLOPT_DEFAULT_PROTOCOL,  CURLOPT_URL
         *  2) set error message buffer : CURLOPT_ERRORBUFFER
         *  3) set upload, read data, in file size and read function :
         *     CURLOPT_UPLOAD, CURLOPT_READFUNCTION, CURLOPT_READDATA,
         *     CURLOPT_INFILESIZE_LARGE
            4) set callback for writing function and write data
         *     CURLOPT_WRITEFUNCTION, CURLOPT_WRITEDATA
         *  5) Perform the request
         *  6) Clean allocated memory for easy interface
         */

        curl_easy_setopt(curl, CURLOPT_URL, url_string.c_str());
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "sftp");

        char errbuf[CURL_ERROR_SIZE];
        memset(errbuf, '\0', CURL_ERROR_SIZE);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, readCallback);
        curl_easy_setopt(curl, CURLOPT_READDATA, argv[3]);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, file_size);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &recvBuffer);

        CURLcode rc = curl_easy_perform(curl);
        if ( rc != CURLE_OK ) {
            std::cout << "curl_easy_perform not OK " << rc << std::endl;
            std::cout << "--> " << curl_easy_strerror(rc) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    /*
     *  clean global initialization allocated memory
     */

    curl_global_cleanup();
    return (EXIT_SUCCESS);
}
