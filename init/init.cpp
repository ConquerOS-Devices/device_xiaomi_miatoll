/*
 * Copyright (C) 2020 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdlib>
#include <cstring>
#include <sys/sysinfo.h>
#include <vector>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "init_common.h"
#include "vendor_init.h"

using android::base::GetProperty;
using std::string;

std::vector<std::string> ro_props_default_source_order = {
    "",
    "odm.",
    "product.",
    "system.",
    "vendor.",
    "system_ext.",
    "conquer.",
};

void property_override(string prop, string value)
{
    auto pi = (prop_info*) __system_property_find(prop.c_str());
    if (pi != nullptr)
        __system_property_update(pi, value.c_str(), value.size());
    else
        __system_property_add(prop.c_str(), prop.size(), value.c_str(), value.size());
}

void set_ro_build_prop(const std::string &source, const std::string &prop,
        const std::string &value, bool product = false) {
    std::string prop_name;

    if (product) {
        prop_name = "ro.product." + source + prop;
    } else {
        prop_name = "ro." + source + "build." + prop;
    }

    property_override(prop_name.c_str(), value.c_str(), false);
}

void set_device_props(const std::string brand, const std::string device, const std::string model) {
    for (const auto &source : ro_props_default_source_order) {
        set_ro_build_prop(source, "brand", brand, true);
        set_ro_build_prop(source, "device", device, true);
        set_ro_build_prop(source, "model", model, true);
    }

}

void load_device_properties() {
    property_override("ro.build.fingerprint", "google/redfin/redfin:11/RQ2A.210405.005/7181113:user/release-keys");
    property_override("ro.build.description", "redfin-user 11 RQ2A.210405.005 7181113 release-keys");
    std::string hwname = GetProperty("ro.boot.hwname", "");
    std::string region = GetProperty("ro.boot.hwc", "");

    if (hwname == "curtana") {
        if (region == "Global_TWO") {
            set_device_props(
                    "Redmi", "curtana", "Redmi Note 9S");
        } else if (region == "India") {
            set_device_props(
                    "Redmi", "curtana", "Redmi Note 9 Pro");
        } else if (region == "Japan") {
            set_device_props(
                    "Redmi", "curtana", "Redmi Note 9S");
        }
    } else if (hwname == "excalibur") {
        set_device_props(
                "Redmi", "excalibur", "Redmi Note 9 Pro Max");
    } else if (hwname == "gram") {
        set_device_props(
                "POCO", "gram", "POCO M2 Pro");
    } else if (hwname == "joyeuse") {
        set_device_props(
                "Redmi", "joyeuse", "Redmi Note 9 Pro");
    }
}

void load_hardware_properties() {
    string hwversion = GetProperty("ro.boot.hwversion", "");
    property_override("ro.boot.hardware.revision", hwversion); 
}

void vendor_load_properties() {
    load_common_properties();
    load_device_properties();
    load_hardware_properties();
}
