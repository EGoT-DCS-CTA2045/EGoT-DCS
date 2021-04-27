#!/bin/bash
# Basic while loop
ctr=$1
while [ $ctr -le 10 ]
do
openssl genrsa -out clients/client$ctr.key 2048
openssl req -new -key clients/client$ctr.key -out clients/client$ctr.req -subj "/C=US/ST=OR/L=Portland/O=Portland State University/OU=Power Lab Department/CN=www.localhost.com"
openssl x509 -req -in clients/client$ctr.req -CA CA.crt -CAkey CA.key -set_serial 0x3E8  -extensions server -days 3650 -outform PEM -out clients/client$ctr.crt
((ctr++))
done
echo All done