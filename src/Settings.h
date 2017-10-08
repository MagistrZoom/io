//
// Created by izoomko on 10/14/17.
//

#pragma once

// Bitmask
enum CaptureFields
{
    CaptureFieldsSettings = 0x7, // ICM
    CaptureFieldsBufferNonEmpty = 0x8, // ICBNE
    CaptureFieldsBufferFilled = 0x10, // ICOV
    CaptureFieldsBufferTimerMode = 0x48 // ICTMR
};
enum CaptureTimerSettings
{ // ICTMR
    CaptureTimerSettingsDisabled = 0,
    CaptureTimerSettingsTimerOne = 1,
    CaptureTimerSettingsTimerTwo = 2,
    CaptureTimerSettingsBoth = 3
};
enum CaptureSettings
{ // ICM
    CaptureSettingsDisabled = 0x0,
    CaptureSettingsStoreAtAnyFront = 0x1,
    CaptureSettingsStoreAtFadingFront = 0x2,
    CaptureSettingsStoreAtRisingFront = 0x3,
    CaptureSettingsStoreAtForthRisingFront = 0x4,
    CaptureSettingsStoreAtSixteenthRisingFront = 0x5,
    CaptureSettingsStoreAtForthFadingFront = 0x6,
    CaptureSettingsStoreAtSixteenthFadingFront = 0x7,
};
