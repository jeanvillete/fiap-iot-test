## 1 - Node-Red via Docker

É possível obter o código JavaScript no node-red e executá-lo diretamente no **node** do host
corrente, mas a minha preferência foi executá-lo via Docker.

```
$ docker run -p 1880:1880 \
    --privileged \
    -v /dev/ttyACM0:/dev/ttyACM0 \
    --name fiap-iot-test \
    --rm \
    nodered/node-red
```

**Nota**: Observar a presença do parâmetro ```--rm``` no qual indica que o container criado
será excluído quando o processo em questão for finalizado.

## 2 - node-red-node-serialport

Como no projeto de maneira geral eu converso com a placa através de comandos que trafegam via
porta serial, é necessário instalar no node-red a biblioteca/Pallete **node-red-node-serialport**.

**Nota**: No momento que este texto é escrito a versão mais recente era; 0.13.0

## 3 - importação do fluxo

Agora com Node-Red no ar, e com o Pallete **node-red-node-serialport** devidamente instalado,
importe o arquivo do diretório corrente com o fluxo mapeado; **fiap-iot-test-flow.json**

```
O fluxo disponível tem nas definições de endpoint do componente de WebSocket (in/out)
    o endpoint da minha stack (API Gateway) que eu subi no na AWS.
Caso você tenha subido sua própria stack, lembre-se de alterar esta informação após
    importar o fluxo para o Node-Red.
```
