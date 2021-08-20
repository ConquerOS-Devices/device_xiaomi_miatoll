# Copyright (C) 2021 LineageOS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

$(call inherit-product, device/xiaomi/miatoll/device.mk)
$(call inherit-product, vendor/conquer/config/common.mk)

# Bootanimation Resolution
TARGET_BOOT_ANIMATION_RES := 1080

PRODUCT_NAME := conquer_miatoll
PRODUCT_DEVICE := miatoll
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := Redmi Note 9S
PRODUCT_MANUFACTURER := Xiaomi

CONQUER_BUILD_TYPE := OFFICIAL
TARGET_USE_GAPPS := true

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi
IS_PHONE := true

