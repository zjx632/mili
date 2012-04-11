/*
binary_streams: A minimal library supporting encoding of different data
                types in a single binary stream.
    Copyright (C) 2012 Matias Tripode, FuDePAN

    This file is part of the MiLi Minimalistic Library.

    MiLi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MiLi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MiLi.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BINARY_STREAMS_HELPERS_H
#define BINARY_STREAMS_HELPERS_H


#include <string>
#include <assert.h>
#include <stdint.h>
#include <stdexcept>
#include <typeinfo>

#include "compile_assert.h"
#include "generic_exception.h"
#include "template_info.h"
#include "container_utils.h"


NAMESPACE_BEGIN


class BstreamExceptionHierarchy {};

typedef GenericException<BstreamExceptionHierarchy> BstreamException;

DEFINE_SPECIFIC_EXCEPTION_TEXT(container_not_finished,
                               BstreamExceptionHierarchy,
                               "More elements were expected to be written.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(container_finished,
                               BstreamExceptionHierarchy,
                               "The container was finished already.");


DEFINE_SPECIFIC_EXCEPTION_TEXT(stream_too_small,
                               BstreamExceptionHierarchy,
                               "Stream is too small for read size, maybe not a container.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(skip_excess,
                               BstreamExceptionHierarchy,
                               "Trying to skip too much.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(type_too_large,
                               BstreamExceptionHierarchy,
                               "The string can't be read from the stream.");

DEFINE_SPECIFIC_EXCEPTION_TEXT(type_mismatch,
                               mili::BstreamExceptionHierarchy,
                               "Types of input and output streams mismatch.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(type_size_mismatch,
                               mili::BstreamExceptionHierarchy,
                               "Types of input and output streams mismatch in size.");


typedef std::string EncodingType;


/** Holds encode/decode information usefull for report/error checking     */
struct DecodeInfoType
{
    //size of the type in the current platform
    uint32_t currentPlatformTypeSize;
    //data type in the current platform
    std::string currentPlatformType;
    //size of the type in the previous platform
    uint32_t originalTypeSize;
    //data type in the previous platform
    std::string originalType;

} ;

/**
* NAMESPACE TO AVOID NAME CONFLICTS
*/
namespace HelperFunctions
{

/** appends value toBeAppended to destionation     */
template <typename T>
static inline void append(mili::EncodingType& destination, const T toBeAppended)
{
    destination.append(reinterpret_cast<const char*>(&toBeAppended), sizeof(toBeAppended));
}

/** Copies from source to destination      */
template <typename T>
static inline uint32_t copy(const mili::EncodingType& source, T& destination, uint32_t& pos)
{
    return source.copy(reinterpret_cast<char*>(&destination), sizeof(destination), pos);
}

template <uint32_t>
static inline uint32_t copy(const mili::EncodingType& source, uint32_t& destination, uint32_t pos)
{
    return source.copy(reinterpret_cast<char*>(&destination), sizeof(destination), pos);
}
};



/**
* TEMPLATE STRUCT HELPER THAT DESCRIBES THE TYPE
*/

template <class T>
struct TypeDescriber
{
    //Encodes type information
    //appends on _s typeName, typeNameSize, typeSize
    // e.g:   for      int,    3           , 4 (32bits architecture)
    static void encode(EncodingType& _s)
    {
        const std::string typeName(typeid(T).name());
        const uint32_t nameSize(typeName.size());
        const uint32_t typeSize(sizeof(T));

        HelperFunctions::append<uint32_t>(_s, nameSize);

        _s += typeName;

        HelperFunctions::append<uint32_t>(_s, typeSize);

    }
    static void decode(uint32_t& _pos, EncodingType& _s, DecodeInfoType& decodeData)
    {
        decodeData.currentPlatformType = typeid(T).name();
        uint32_t nameSize;

        decodeData.currentPlatformTypeSize  = sizeof(T);

        //Get name from bistream
        _pos += HelperFunctions::copy<uint32_t>(_s, nameSize, _pos);

        decodeData.originalType = _s.substr(_pos, nameSize);
        _pos += nameSize;

        //Get size from bistream
        _pos += HelperFunctions::copy<uint32_t>(_s, decodeData.originalTypeSize, _pos);

    }
};


/*******************************************************************************
 * CHECKING DECODED INFO POLICY.
 ******************************************************************************/

/** Policy that check and displays on std::cerr whether there was some erros during reading data from bistream   */
struct CheckAndCerrPolicy
{
    static void check(const DecodeInfoType& decodedInfo)
    {
        if (decodedInfo.currentPlatformType != decodedInfo.originalType)
        {
            std::cerr << "Current type: " << decodedInfo.currentPlatformType << ", is different from decoded one: " << decodedInfo.originalType;
        }
        if (decodedInfo.currentPlatformTypeSize != decodedInfo.currentPlatformTypeSize)
        {
            std::cerr << "Current type size: " << decodedInfo.currentPlatformTypeSize << ", is different from decoded one: " << decodedInfo.currentPlatformTypeSize;
        }
    }
};

/** Policy that check and throws exception whether there was some erros during reading data from bistream   */
struct CheckAndThrowPolicy
{
    static void check(const DecodeInfoType& decodedInfo)
    {
        if (decodedInfo.currentPlatformTypeSize != decodedInfo.originalTypeSize)
        {
            throw type_size_mismatch();
        }
        if (decodedInfo.currentPlatformType != decodedInfo.originalType)
        {
            throw type_mismatch();
        }
    }
};

/** Check whether there was some erros during reading data from bistream   */
template < class CheckErrorPolicy = CheckAndThrowPolicy >
struct CheckDecodeInfo
{
    static void check(const DecodeInfoType& decodeInfo)
    {
        CheckErrorPolicy::check(decodeInfo);
    }
};

/*******************************************************************************
 * DEBUGGING POLICY.
 ******************************************************************************/

/**
 * DebugPolicyBostream enables debugging info for bostream
 * @param T : Type of the object/value to be written into bostream
 */
template <typename T>
struct DebugPolicyBostream
{
    static void debug(EncodingType& _s)
    {
        TypeDescriber<T>::encode(_s);
    }
};

/**
 * DebugPolicyBistream enables debugging info for bistream
 * @param T : Type of the object/value to be read from bistream
 */
template <typename T>
struct DebugPolicyBistream
{
    /** Check whether there was some erros during reading data from bistream   */
    static void debug(uint32_t& _pos, EncodingType& _s, DecodeInfoType& decodeInfo)
    {
        TypeDescriber<T>::decode(_pos, _s, decodeInfo);
        CheckDecodeInfo<CheckAndThrowPolicy>::check(decodeInfo);
    }
};



/**
 * NoDebugPolicyBostream makes not debugging info for bostream
 * @param T : Type of the object/value to be written to bostream
 */
template <typename T>
struct NoDebugPolicyBostream
{
    static void debug(EncodingType&) {}
};

/**
 * NoDebugPolicyBistream makes not debugging info for bistream
 * @param T : Type of the object/value to be read from bistream
 */
template <typename T>
struct NoDebugPolicyBistream
{
    static void debug(uint32_t&, EncodingType&, DecodeInfoType&) {}
};


NAMESPACE_END

#endif
