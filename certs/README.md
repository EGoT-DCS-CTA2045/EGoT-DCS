Create a self-signed certificate authority (a private key pair):  

```shell
openssl req -newkey rsa:4096             -x509             -sha256             -days 3650             -nodes             -out CA.crt             -keyout CA.key             -subj "/C=US/ST=OR/L=Portland/O=Portland State University/OU=Power Lab Department/CN=www.localhost.com"
```

Generate a server key pair:

```shell
openssl genrsa -out server/server.key 2048
openssl req -new -key server/server.key -out server/server.req -subj "/C=US/ST=OR/L=Portland/O=Portland State University/OU=Power Lab Department/CN=www.localhost.com"
openssl x509 -req -in server/server.req -CA CA.crt -CAkey CA.key -set_serial 0x3E8  -extensions server -days 3650 -outform PEM -out server/server.crt 
```

Generate a clients key pair:

```shell
openssl genrsa -out clients/client.key 2048
openssl req -new -key clients/client.key -out clients/client.req -subj "/C=US/ST=OR/L=Portland/O=Portland State University/OU=Power Lab Department/CN=www.localhost.com"
openssl x509 -req -in clients/client.req -CA CA.crt -CAkey CA.key -set_serial 0x3E8  -extensions server -days 3650 -outform PEM -out clients/client.crt 
```

To expidite the client generation run the bash script to generate the specified number of certs:

```shell
chmod u+x cert_gen.sh
./cert_gen.sh 10
```