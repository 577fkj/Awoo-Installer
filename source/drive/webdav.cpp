#include "webdav.hpp"
#include "util/lang.hpp"
#include "util/config.hpp"
#include "ui/MainApplication.hpp"
#include <curl/curl.h>
#include <tinyxml2.h>
#include <regex>

namespace inst::ui
{
    extern MainApplication *mainApp;
}

using json = nlohmann::json;

namespace inst::drive
{

    std::string extractServerAddress(const std::string &url)
    {
        std::regex regex("^(https?://[^/?#]+)");
        std::smatch match;

        if (std::regex_search(url, match, regex))
        {
            return match[1].str();
        }

        return "";
    }

    void webdav::set_auth(const std::string &username, const std::string &password)
    {
        this->setUsernameAndPassword(username, password);
    }

    drive::entries webdav::list(const std::string &path)
    {
        std::string server_address = extractServerAddress(path);
        std::string xmlData = this->sendCustomMethod(path, "PROPFIND", {"Depth: 1"});

        entries list;
        tinyxml2::XMLDocument doc;
        doc.Parse(xmlData.c_str());

        tinyxml2::XMLElement *multistatusElement = doc.FirstChildElement("D:multistatus");
        if (multistatusElement)
        {
            tinyxml2::XMLElement *responseElement = multistatusElement->FirstChildElement("D:response");
            responseElement = responseElement->NextSiblingElement("D:response"); // keep self
            while (responseElement)
            {
                tinyxml2::XMLElement *hrefElement = responseElement->FirstChildElement("D:href");
                tinyxml2::XMLElement *propstatElement = responseElement->FirstChildElement("D:propstat");
                if (hrefElement && propstatElement)
                {
                    tinyxml2::XMLElement *propElement = propstatElement->FirstChildElement("D:prop");
                    if (propElement)
                    {
                        tinyxml2::XMLElement *displayNameElement = propElement->FirstChildElement("D:displayname");
                        tinyxml2::XMLElement *resourcetypeElement = propElement->FirstChildElement("D:resourcetype");
                        if (displayNameElement && resourcetypeElement)
                        {
                            std::string name = displayNameElement->GetText();
                            std::string id = server_address + hrefElement->GetText();
                            bool isFolder = (resourcetypeElement->FirstChildElement("D:collection") != nullptr);
                            if (name != "." && name != "..")
                            {
                                list.push_back({id, name, isFolder});
                            }
                        }
                    }
                }

                responseElement = responseElement->NextSiblingElement("D:response");
            }
        }
        return list;
    }
}