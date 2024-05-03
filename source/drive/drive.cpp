#include "drive.hpp"
#include "httpindex.hpp"
#include "aliyundrive.hpp"
#include "webdav.hpp"

namespace inst::drive {

drive::ref new_drive(drive_type type) {
    switch (type) {
    case dt_httpdir:
        return std::make_shared<httpdir>();
    case dt_alidrive:
        return std::make_shared<aliyundrive>();
    case dt_webdav:
        return std::make_shared<webdav>();
    default:
        throw std::runtime_error("unsupport drive type");
    }
}

}