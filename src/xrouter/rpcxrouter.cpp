#include "json/json_spirit_reader_template.h"
#include "json/json_spirit_writer_template.h"
#include "json/json_spirit_utils.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <exception>
#include <iostream>

#include "xrouterapp.h"
#include "uint256.h"
using namespace json_spirit;

//******************************************************************************
//******************************************************************************
Value xrGetBlocks(const Array & params, bool fHelp)
{
    if (fHelp) {
        throw std::runtime_error("xrGetBlocks\nLookup blocks in a specified blockchain.");
    }

    if (params.size() < 1)
    {
        Object error;
        error.emplace_back(Pair("error", "Currency not specified"));
        error.emplace_back(Pair("name",     __FUNCTION__));
        return error;
    }

    if (params.size() < 2)
    {
        Object error;
        error.emplace_back(Pair("error", "Block hash not specified"));
        error.emplace_back(Pair("name",     __FUNCTION__));
        return error;
    }

    std::string currency    = params[0].get_str();
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string id = boost::uuids::to_string(uuid);
    Object result;

    auto statusCode = xrouter::App::instance().getBlocks(id, currency, params[1].get_str());
    if (statusCode == xrouter::SUCCESS) {
        Object obj;
        obj.emplace_back(Pair("query-id", id));
        return obj;
    } else {
        Object error;
        error.emplace_back(json_spirit::Pair("error", ""));
        error.emplace_back(json_spirit::Pair("code", statusCode));
        error.emplace_back(json_spirit::Pair("name", __FUNCTION__));
        return error;
    }
}

Value xrGetReply(const Array & params, bool fHelp)
{
    if (fHelp) {
        throw std::runtime_error("xrGetBlocks\nLookup blocks in a specified blockchain.");
    }

    if (params.size() < 1)
    {
        Object error;
        error.emplace_back(Pair("error", "Query ID not specified"));
        error.emplace_back(Pair("name",     __FUNCTION__));
        return error;
    }

    std::string uuid = params[0].get_str();
    std::string reply = xrouter::App::instance().getReply(uuid);
    Object obj;
    obj.emplace_back(Pair("reply", reply));
    return obj;
}
