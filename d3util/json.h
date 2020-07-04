#ifndef JSOND3Util_H
#define JSOND3Util_H

#include <type_traits>
#include <mor/mor.h>
#include <json/json.h>
#include <memory>
#include <exception>
#include <d3util/stacktrace.h>
#include <d3util/datetime.h>
#include <functional>

struct JsonIgnoreWrite{};

template<class T>
struct JsonConvertWrite{
  std::function<void(Json::Value&, const T&)> converter;
  JsonConvertWrite(std::function<void(Json::Value&, const T&)> converter) : converter(converter){}
};

struct JSONObject : public Json::Value
{
    JSONObject(const Json::Value& value);
    JSONObject(Json::Value&& value);
    JSONObject(Json::ValueType type = Json::nullValue);
    virtual ~JSONObject() = default;

    JSONObject& operator =(const Json::Value& value);
    JSONObject& operator =(Json::Value&& value);

    operator std::string ();
};

struct JSONArray : public JSONObject
{
    JSONArray();
    JSONArray(Json::Value&& outro);
    JSONArray(const Json::Value& outro);


    JSONObject& operator =(const Json::Value& value);
    JSONObject& operator =(Json::Value&& value);
};


inline void to_json(const std::string& strJson, Json::Value& json)
{
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader{builder.newCharReader()};

    std::string errors;

    bool parsingSuccessful = reader->parse(
        strJson.c_str(),
        strJson.c_str() + strJson.size(),
        &json,
        &errors
    );

    if (!parsingSuccessful) {
        errors += '\n' +strJson.substr(0, 200);
        throw_with_trace(std::runtime_error("Failed to parse the JSON, errors: "+errors));
    }
}

inline Json::Value to_json(const std::string str)
{
    Json::Value json;
    to_json(str, json);
    return json;
}


struct converter_to_json
{
    Json::Value json;

    template<class FieldData, class Annotations>
    void operator()(FieldData f, Annotations a, int qtd)
    {
        const char* name = f.name();
        if( ! (JsonIgnoreWrite*) Annotations::get_field(name) ){
            JsonConvertWrite<typename FieldData::type>* convWrite = Annotations::get_field(name);
            if(convWrite)
                convWrite->converter(json, f.get());
            else
                get( f.get(), name );
        }
    }

    #define IS_ULONG (std::is_same<const long, T>::value || std::is_same<const unsigned long, T>::value || std::is_same<const unsigned long long, T>::value)

    template <class T>
    auto get(T& val, const char* name) noexcept -> std::enable_if_t<(std::is_convertible<T, datetime>::value || std::is_enum<T>::value)>
    {
        json[name] = to_string(val);
    }

    template <class T, class Dummy = void>
    auto get(T& val, const char* name) noexcept -> std::enable_if_t<IS_ULONG>
    {
        json[name] = (Json::UInt64) val;
    }

    template <class T, class Dummy = void>
    auto get(T& val, const char* name) noexcept -> std::enable_if_t<(is_simple_type<T>::value && !std::is_enum<T>::value && !IS_ULONG)>
    {
        json[name] = val;
    }

    template <class T, class Dummy = void>
    auto get(T& val, const char* name) noexcept -> std::enable_if_t<!is_simple_type<T>::value 
    && !std::is_convertible<T, datetime>::value 
    && !std::is_enum<T>::value>
    {
        converter_to_json tj;
        reflector::visit_each(val, tj);
        json[name] = tj.json;
    }
};

template<class Entity>
Json::Value to_json(const Entity& entity)
{
    converter_to_json cj;
    reflector::visit_each(entity, cj);
    return cj.json;
}

struct from_json
{
    Json::Value* json_;
    bool dealoc_ = false;

    from_json(const Json::Value& json);
    from_json(const std::string& string);
    ~from_json();
    
//    template<class Field>
//    void value_to_field(Json::Value v, Field f){}
    void value_to_field(Json::Value v, std::string &&f);
    void value_to_field(Json::Value v, int &&f);
    void value_to_field(Json::Value v, long &&f);
    void value_to_field(Json::Value v, float &&f);
    void value_to_field(Json::Value v, double &&f);
    void value_to_field(Json::Value v, short &&f);
    void value_to_field(Json::Value v, long long &&f);
    void value_to_field(Json::Value v, unsigned int &&f);
    void value_to_field(Json::Value v, unsigned short &&f);
    void value_to_field(Json::Value v, unsigned long &&f);
    void value_to_field(Json::Value v, unsigned long long &&f);
    void value_to_field(Json::Value v, datetime &&f);
    void value_to_field(Json::Value v, bool &&f);

    template <class T, class Dummy = void>
    auto get(T& val, const char* name) noexcept -> std::enable_if_t<std::is_enum<T>::value>
    {
        JSONObject value = json_->get(name, Json::Value::null);
        if(value.isIntegral())
            val = static_cast<T>(value.asInt());
        else if(value.isString()){
            std::stringstream ss{value.asString()};
            ss >> val;
        }
    }

    template <class T, class Dummy = void>
    auto get(T& val, const char* name) noexcept -> std::enable_if_t<is_simple_or_datatime_type<T>::value
                                                            && !std::is_enum<T>::value>
    {
        JSONObject value = json_->get(name, Json::Value::null);
        if(value != Json::Value::null)
            value_to_field(value , std::move(val));
    }

    template <class T, class Dummy = void>
    auto get(T& val, const char* name) noexcept -> std::enable_if_t<!is_simple_or_datatime_type<T>::value >
    {
        JSONObject obj = (*json_)[name];
        if(obj.isObject()){
            from_json fj(obj);
            reflector::visit_each(val, fj);
        }
    }

    template<class FieldData, class Annotations>
    void operator()(FieldData f, Annotations e, int lenght)
    {
        auto& val = f.get();
        get( val, f.name() );
    }

    template <typename T>
    operator T () {
        T ret{};
        reflector::visit_each(ret, *this);
        return ret;
    }
};

template<class T>
inline void set_from_json(T& obj, const JSONObject& json)
{
    if(json.isObject() || json.isNull()){
        from_json fj{json};
        reflector::visit_each(obj, fj);
    }
}

#endif // JSON_H
