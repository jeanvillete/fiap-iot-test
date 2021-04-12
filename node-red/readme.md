# start node-red through a docker container
    $ docker run -p 1880:1880 --privileged -v /dev/ttyACM0:/dev/ttyACM0 --name fiap-iot-test --rm nodered/node-red

# with node-red up and running, first of all, install the Palette below;
  - node-red-node-serialport
  - at the moment this is written, the version found and used is 0.13.0

# import the flow fiap-iot-test-flow.json
    - import the file available on this directory; fiap-iot-test-flow.json