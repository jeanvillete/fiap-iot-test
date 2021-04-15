## 3.1 - AWS

Os recursos sob o diretório corrente são para deploy dos componentes da AWS.

Todos os recursos estão declarados no artefato **serverless.yml**.

- **DynamoDB**; com estrutura de dados que permite o pareamento entre o dispositivo
(Arduino + node-red) e o cliente via web browser. O DynamoDB é essencial
para comunicação WebSocket.
- **API Gateway**; com as rotas do WebSocket
- **Serviços Lambda**; respondendo a cada tipo/rota de mensagem estabelecido no
API Gateway
- **IAM Roles**; com as permissões a cada serviço exposto e invocado.

```
Este deploy da AWS é facultativo, pois eu já tenho exposto o endpoint;
    wss://uj09gm4nf8.execute-api.us-east-1.amazonaws.com/dev
    que pode ser utilizado caso o seu objetivo não seja testar os componentes
    da AWS.
```

## 3.2 - ferramenta de deploy

A ferramenta que eu utilizei para deploy na AWS é o [serverless](https://www.npmjs.com/package/serverless) disponível através do gestor de pacotes **npm**.

    $ npm install serverless -g

**Nota**: Esta ferramenta faz utilização dos artefatos/aplicativo do cliente da AWS (aws-cli),
então no mínimo o arquivo da sessão do usuário/cliente **~/.aws/credentials** deve estar
disponível e com conteúdo atualizado.

# 3.3 - aplicando o deploy

```
# deve estar no mesmo diretório do artefato serverless.yml
$ serverless deploy
```

**Nota**: A saída/output deste comando tem o status dos serviços deployados, junto com a url
do **API Gateway** para o WebSocket.

```
Este deploy da AWS é facultativo, pois eu já tenho exposto o endpoint;
    wss://uj09gm4nf8.execute-api.us-east-1.amazonaws.com/dev
    que pode ser utilizado caso o seu objetivo não seja testar os componentes
    da AWS.
```