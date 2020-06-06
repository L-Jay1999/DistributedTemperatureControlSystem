#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "request_payload.h"
#include "requests.h"

class RequestController
{
public:
    static QByteArray Request(const QByteArray &request)
    {
        QJsonDocument document;
        auto [is_parsing_suc, request_parsed] = RequestParser::Parse(request);
        if (!is_parsing_suc)
        {
            auto fail_response = getAckResponse(false);
            document.setObject(fail_response.ToQJsonObject());
            return document.toJson();
        }

        switch (request_parsed.type)
        {
            // ......
        }

        return document.toJson();

    }
};

#endif // REQUEST_CONTROLLER_H
