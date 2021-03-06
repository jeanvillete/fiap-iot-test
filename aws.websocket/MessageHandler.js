'use strict'

const AWS = require('aws-sdk');
const dynamo = new AWS.DynamoDB.DocumentClient();

const WEB_SOCKET_MESSAGES_TABLE = process.env.WEB_SOCKET_MESSAGES_TABLE;
const INDEX_PAIR_CODE_WITH_PARTY_TYPE = process.env.INDEX_PAIR_CODE_WITH_PARTY_TYPE;

const SUCCESSFULL_RESPONSE = {
    statusCode: 200,
    body: 'Success'
};

module.exports.handle = (event, context, callback) => {
    sendMessageToPartiesPaired(event)
        .then(() => {
            callback(null, SUCCESSFULL_RESPONSE);
        })
        .catch((err) => {
            callback(failedResponse(500, JSON.stringify(err)));
        });
}

const sendMessageToPartiesPaired = (event) => {
    const {data} = JSON.parse(event.body);
    const {pairCode, targetPartyType} = data;

    return getTargetPartiesConnectionId(pairCode, targetPartyType)
        .then(dynamoDbData => {
            return dynamoDbData.Items
                .map(dynamoDbDataItem => 
                    dynamoDbDataItem.connectionId
                )
                .map(targetPartyConnectionId =>
                    sendMessageToPartyPaired(targetPartyConnectionId, data, event)
                );
        });
}

const getTargetPartiesConnectionId = (pairCode, targetPartyType) => {
    const params = {
        TableName: WEB_SOCKET_MESSAGES_TABLE,
        IndexName: INDEX_PAIR_CODE_WITH_PARTY_TYPE,
        KeyConditionExpression: 'pairCode = :paramPairCode AND partyType = :paramPartyType',
        ExpressionAttributeValues: {
            ':paramPairCode': pairCode,
            ':paramPartyType': targetPartyType
        },
        ProjectionExpression: 'connectionId'
    }

    return dynamo
        .query(params)
        .promise();
}

const sendMessageToPartyPaired = (targetPartyConnectionId, {message}, event) => {
    const messageAsString = JSON.stringify(message);

    const connectionEndpoint = event.requestContext.domainName + '/' + event.requestContext.stage;

    const apiGatewayManagementApi = new AWS.ApiGatewayManagementApi(
        {
            apiVersion: '2018-11-29',
            endpoint: connectionEndpoint
        }
    );

    const params = {
        ConnectionId: targetPartyConnectionId,
        Data: messageAsString
    }

    return apiGatewayManagementApi
        .postToConnection(params)
        .promise();
}


const failedResponse = (statusCode, error) => (
    {
        statusCode,
        body: error
    }
);