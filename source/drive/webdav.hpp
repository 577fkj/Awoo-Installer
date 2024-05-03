#pragma once

#include "util/drive.hpp"
#include "util/curl.hpp"
#include "util/json.hpp"

namespace inst::drive {
    class webdav : public drive, public curl::client {
    public:
        drive_type getType() { return dt_webdav; }

        void set_auth(const std::string& username, const std::string& password);
        entries list(const std::string& file_id);
    private:
    };
}