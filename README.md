###### Escola: FIAP
###### Curso: MBA FULLSTACK DEVELOPER, MICROSERVICES, CLOUD & IoT
###### Disciplina: IoT Development
###### Professor: RICARDO DA SILVA OGLIARI
###### Aluno / RM: JEAN BRUNO SOUTO VILLETE / 335435


```
Objetivo principal: O trabalho consiste na entrega de uma solução IoT completa.

Detalhe da entrega: entregar a descrição do projeto textual ou em vídeo (pode subir o vídeo
    no YouTube, deixar como não listado e enviar o link). Além da descrição, imagens 
    ilustrativas e snippets de código que demonstrem a integração dos componentes 
    são requeridas. 

Por ex: uma solução que integra um sensor de temperatura a uma nuvem do Google com Firebase.
    Nesta caso, imagens do circuito montada da placa, sensores e atuadores, trechos de
    código que mostrem como foi feita a integração da placa com Fog e/ou Cloud computing. 
```

# 1 - solução proposta

O trabalho proposto é a interação entre um componente físico (sensor) plugado no arduino, e um serviço remoto,
gerido em uma plataforma como AWS, Azure ou Google Cloud Platform.

Dado os componentes que eu tinha em mãos e o meu conhecimento em cloud, o resultado foi basicamente
utilizar um sensor ultrasonico de presença (HC-SR04), e comunicar com um serviço WebSocket hospedado na 
AWS, em que pudesse mostrar a distância calculada pelo sensor em tempo real, através de uma página web.

Mas além de mostrar que meu sensor se comunicava devidamente com o cliente remoto via WebSocket,
eu decidi implementar o registro do meu device (circuito e o conjunto dos componentes físicos) associando
a um usuário, e a mensagem gerada pelo sensor pudesse ser disparada apenas para o usuário remoto de fato
interessado.

Esta segunda parte é um **plus** no trabalho, pois mostra além da comunicação mínima do componente/sensor
com a internet, mostra também uma **inteligência no pareamento** entre o físico e o serviço remoto na internet.

# 2 - interface <TL;DR>

Imagem panorâmica do circuito;

##### Nota: maiores detalhes do circuito está na [seção abaixo de montagem e deployment do Arduino.](https://github.com/jeanvillete/fiap-iot-test/tree/master/arduino)

![](imgs/A_fiap-iot-test-board-overview.JPG)

--

Quando a placa é energizada, todos os componentes e sensores ficam desligados, i.e; leds e 
sensor ultrasonico de distância.

Na **bread board**, na extrema esquerda, há um push button;

![](imgs/B_fiap-iot-test-push_button-pairing.jpg)

--

Quando este push button é pressionado, é feito uma requisição solicitando um código de pareamento.

    Toda comunicação com a placa Arduino e o mundo externo/remoto, é feita utilizando
    a porta serial (SERIAL_BAUDS 9600).

Este código de pareamento é registrado remotamente no banco DynamoDB na AWS, que posteriormente
será pareado com um cliente remoto acessando a página web (para comunicação websocket).

O código de pareamento é formado por 4 dígitos que vão de 1 a 4, e.g; 1234, 2244, 4121, etc.

    Este requisito do código de pareamento, é basicamente porque eu não tenho um  display
    para apresentar o código, e como eu tenho apenas leds, eu utilizei 4 leds (dígitos de
    1 a 4) que acendem e desligam em uma ordem que apresentam os 4 dígitos (cada dígito
    por vez).

Quando um código de pareamento é recepcionado pela placa, este código é apresentado através dos
leds responsáveis;

![](imgs/C_fiap-iot-test-leds-pairing_code_digits.jpg)

--

Uma vez que o usuário consiga obter este código de pareamento, o usuário deve acessar página web
com capacidade de comunicar/parear/recepcionar mensagens, se conectar ao websocket e por ultimo
submeter o código de pareamento;

![](imgs/E_fiap-iot-test-web_page.jpg)

--

Assim que for submetido o código de pareamento pelo usuário via web browser, é disparado uma
mensagem para o disposivo (placa Arduino) informando do evento de pareamento, então a partir deste
momento o led do status de pareamento é ligado, e o sensor ultrasonico de distância começa a
observar o ambiente e disparar a distância do corpo mais próximo a cada **500 milissegundos**;

![](imgs/D_fiap-iot-test-led-pairing_status.JPG)

--

# 3 - deployment

Abaixo segue os componentes e a stack da solução proposta no trabalho.

- AWS; [clique aqui para os passos do deployment dos componentes da AWS](https://github.com/jeanvillete/fiap-iot-test/tree/master/aws.websocket)
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

- Arduino; [clique aqui para os passos da montagem e deploy do código na placa Arduino](https://github.com/jeanvillete/fiap-iot-test/tree/master/arduino)
    - Desenho esquemático do circuito disponível
    - Bread board
    - Circuito
    - Leds
    - Sensor de aproximação

- Node-red; [clique aqui para os passos do deployment do fluxo Node-Red](https://github.com/jeanvillete/fiap-iot-test/tree/master/node-red)
    - (Ponte) Implementação alto nível para comunicação com placa Arduino (porta serial),
    abertura da comunicação WebSocket, recepção e postagem das mensagens.

- Página web remota;
    - SPA (single page application) hospedado remotamente para interação com o device remoto
    via WebSocket.
    - Afim de não apenas deixar o código disponível, eu resolvi deixá-lo também hospedado
    e acessível através do github pages;
        - [página hospedada, clique aqui](https://jeanvillete.github.io/fiap-iot-test/)
        - [repositório com o código, clique aqui](https://github.com/jeanvillete/jeanvillete.github.io/tree/main/fiap-iot-test)