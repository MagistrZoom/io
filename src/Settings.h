//
// Created by izoomko on 10/14/17.
//

#pragma once

// Bitmask
enum CaptureFields
{
    CaptureFieldsSettings = 0x7, // ICM
    CaptureFieldsBufferNonEmpty = 0x8, // ICBNE
    CaptureFieldsBufferOverflow = 0x10, // ICOV
    CaptureFieldsBufferTimerMode = 0x60 // ICTMR
};
enum CaptureTimerSettings
{ // ICTMR
    CaptureTimerSettingsDisabled = 0x0,
    CaptureTimerSettingsTimerOne = 0x20,
    CaptureTimerSettingsTimerTwo = 0x40,
    CaptureTimerSettingsBoth = 0x60
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
