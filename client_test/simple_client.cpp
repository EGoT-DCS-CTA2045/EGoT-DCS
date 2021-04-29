#include <httplib.h>
#include <iostream>
#include <stdlib.h>

int main(void)
{
    //httplib::Client client("192.168.0.178", 8889);
    httplib::Client client("host.docker.internal", 8886); //host.docker.internal serves as an alias for the localhost IPof the host machine (the one running the docker container)

    std::cout << "attempting tests" << std::endl;
    if (auto res = client.Get("/hi")) {
        if (res->status == 200) {
        std::cout << res->body << std::endl;
        }
    } else {
    auto err = res.error();
    }
    for (int i = 0; i < 5; i++)
    {
        std::cout << "attempting post" << std::endl;
        auto res = client.Post("/post", "here is a test post sent from the C++ client", "text/xml");
        //assert(res->status == 200);
        sleep(1);
    }
    return 0;
}