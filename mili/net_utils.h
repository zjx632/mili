/*    
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt in the root directory or
    copy at http://www.boost.org/LICENSE_1_0.txt)

    MiLi IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#ifndef NET_UTILS_H
#define NET_UTILS_H


#include <cstdint>
#include <arpa/inet.h>

NAMESPACE_BEGIN

inline int32_t hton(int32_t value)
{
    return htonl(value);
}

inline int16_t hton(int16_t value)
{
    return htons(value);
}

inline int32_t ntoh(int32_t value)
{
    return ntohl(value);
}

inline int16_t ntoh(int16_t value)
{
    return ntohs(value);
}

inline uint32_t hton(uint32_t value)
{
    return htonl(value);
}

inline uint16_t hton(uint16_t value)
{
    return htons(value);
}

inline uint32_t ntoh(uint32_t value)
{
    return ntohl(value);
}

inline uint16_t ntoh(uint16_t value)
{
    return ntohs(value);
}

NAMESPACE_END

#endif