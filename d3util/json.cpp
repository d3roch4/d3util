#include "json.h"

from_json::from_json(const Json::Value &json) : json_((JSONObject*)&json)
{
    dealoc_ = false;
}

from_json::from_json(const std::string& str) : json_(nullptr)
{
    json_ = new JSONObject();
    dealoc_ = true;
    to_json(str, *json_);
}

from_json::~from_json()
{
    if(dealoc_)
        delete json_;
}

void from_json::value_to_field(Json::Value v, std::string &f)
{
    f.assign(v.asString());
}

void from_json::value_to_field(Json::Value v, int &f)
{
    if(v.isNumeric())
        f = v.asInt();
}

void from_json::value_to_field(Json::Value v, long &f)
{
    if(v.isNumeric())
        f = v.asInt();
}

void from_json::value_to_field(Json::Value v, float &f)
{
    if(v.isNumeric())
        f = v.asFloat();
}

void from_json::value_to_field(Json::Value v, double &f)
{
    if(v.isNumeric())
        f = v.asDouble();
}

void from_json::value_to_field(Json::Value v, short &f)
{
    if(v.isNumeric())
        f = v.asInt();
}

void from_json::value_to_field(Json::Value v, unsigned int &f)
{
    if(v.isNumeric())
        f = v.asUInt();
}

void from_json::value_to_field(Json::Value v, unsigned short &f)
{
    if(v.isNumeric())
        f = v.asUInt();
}

void from_json::value_to_field(Json::Value v, unsigned long &f)
{
    if(v.isNumeric())
        f = v.asUInt();
}

void from_json::value_to_field(Json::Value v, unsigned long long &f)
{
    if(v.isNumeric())
        f = v.asUInt64();
}

void from_json::value_to_field(Json::Value v, long long &f)
{
    if(v.isNumeric())
        f = v.asInt64();
}

void from_json::value_to_field(Json::Value v, datetime &f)
{
    f = stodt(v.asString());
}

void from_json::value_to_field(Json::Value v, bool &f)
{
    if(v.isBool())
        f = v.asBool();
}

JSONObject::operator std::string() {
    Json::StreamWriterBuilder builder;
    builder["indentation"] = ""; // If you want whitespace-less output
    const std::string output = Json::writeString(builder, *this);
    return output;
}

JSONObject::JSONObject(const Json::Value &value): Json::Value(value){

}

JSONObject::JSONObject(Json::Value &&value): Json::Value(value){

}

JSONObject::JSONObject(Json::ValueType type) : Json::Value(type){

}

JSONObject &JSONObject::operator =(const Json::Value &value){
    Json::Value::operator =(value);
    return *this;
}

JSONObject &JSONObject::operator =(Json::Value &&value){
    Json::Value::operator =(value);
    return *this;
}

JSONArray::JSONArray() : JSONObject(Json::arrayValue){

}

JSONArray::JSONArray(Json::Value &&outro) : JSONObject(outro){

}

JSONArray::JSONArray(const Json::Value &outro) : JSONObject(outro){

}

JSONObject &JSONArray::operator =(const Json::Value &value)
{
    Json::Value::operator =(value);
    return *this;
}

JSONObject &JSONArray::operator =(Json::Value &&value)
{
    Json::Value::operator =(value);
    return *this;
}
