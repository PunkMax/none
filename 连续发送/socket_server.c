#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define server_IP "192.168.1.1"     //服务器IP
#define server_host 1234            //服务器端口号
#define listen_numbers 20           //并发数
#define BUF_SIZE 1024               //缓冲区大小



int main(){
    //创建套接字
    int serv_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(server_IP);  //具体的IP地址
    serv_addr.sin_port = htons(server_host);  //端口
    bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    //进入监听状态，等待用户发起请求
    listen(serv_fd, listen_numbers);

    //接收客户端请求
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    char buffer[BUF_SIZE]={0};

    while (1){
        int client_fd = accept(serv_fd, (struct sockaddr*)&client_addr, &client_addr_size);
        read(client_fd, buffer, sizeof(buffer)-1);
        printf("receive from client: %s \n", buffer);
        close(client_fd);
        memset(buffer,0,sizeof(buffer));
    }

    /*  
    //向客户端发送数据
    char str[] = "hello";
    write(client_fd, str, sizeof(str));
    */
   
    //关闭套接字
    close(serv_fd);

    return 0;
}
