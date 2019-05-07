#include "json.h"

void from_json::value_to_field(Json::Value v, std::string &&f)
{
    f.assign(v.asString());
}

void from_json::value_to_field(Json::Value v, int &&f)
{
    if(v.isNumeric())
        f = v.asInt();
}

void from_json::value_to_field(Json::Value v, long &&f)
{
    if(v.isNumeric())
        f = v.asInt();
}

void from_json::value_to_field(Json::Value v, float &&f)
{
    if(v.isNumeric())
        f = v.asFloat();
}

void from_json::value_to_field(Json::Value v, double &&f)
{
    if(v.isNumeric())
        f = v.asDouble();
}

void from_json::value_to_field(Json::Value v, short &&f)
{
    if(v.isNumeric())
        f = v.asInt();
}

void from_json::value_to_field(Json::Value v, unsigned int &&f)
{
    if(v.isNumeric())
        f = v.asUInt();
}

void from_json::value_to_field(Json::Value v, unsigned short &&f)
{
    if(v.isNumeric())
        f = v.asUInt();
}

void from_json::value_to_field(Json::Value v, unsigned long &&f)
{
    if(v.isNumeric())
        f = v.asUInt();
}

void from_json::value_to_field(Json::Value v, unsigned long long &&f)
{
    if(v.isNumeric())
        f = v.asUInt64();
}

void from_json::value_to_field(Json::Value v, long long &&f)
{
    if(v.isNumeric())
        f = v.asInt64();
}

void from_json::value_to_field(Json::Value v, datetime &&f)
{
    f = stodt(v.asString());
}

void from_json::value_to_field(Json::Value v, bool &&f)
{
    if(v.isBool())
        f = v.asBool();
}
