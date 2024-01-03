/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   LOGO_jpg;
    const int            LOGO_jpgSize = 74478;

    extern const char*   OpenXLSX_lib;
    const int            OpenXLSX_libSize = 2696248;

    extern const char*   OpenXLSXConfig_cmake;
    const int            OpenXLSXConfig_cmakeSize = 58;

    extern const char*   OpenXLSXConfigVersion_cmake;
    const int            OpenXLSXConfigVersion_cmakeSize = 2025;

    extern const char*   OpenXLSXTargetsrelease_cmake;
    const int            OpenXLSXTargetsrelease_cmakeSize = 872;

    extern const char*   OpenXLSXTargets_cmake;
    const int            OpenXLSXTargets_cmakeSize = 3649;

    extern const char*   OpenXLSX_lib2;
    const int            OpenXLSX_lib2Size = 2696248;

    extern const char*   OpenXLSXd_lib;
    const int            OpenXLSXd_libSize = 12541784;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
