#ifndef __LV2_UTIL_H__
#define __LV2_UTIL_H__

#include <ppu-types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _http_uri
{
	u32 scheme;
	u32 hostname;
	u32 username;
	u32 password;
	u32 path;
	u32 port;
	u8 _pad[4];
} httpUri;

typedef struct _http_uri_path
{
	u32 path;
	u32 query;
	u32 fragment;
} httpUriPath;

typedef struct _http_status_line
{
	u32 protocol;
	u32 majorVersion;
	u32 minorVersion;
	u32 reasonPhrase;
	s32 statusCode;
	u8 _pad[4];
} httpStatusLine;

typedef struct _http_request_line
{
	u32 method;
	u32 path;
	u32 protocol;
	u32 majorVersion;
	u32 minorVersion;
} httpRequestLine;

typedef struct _http_header
{
	u32 name;
	u32 value;
} httpHeader;

s32 httpUtilParseUri(httpUri *uri, const char *str, void *pool,	size_t size, size_t *required);
s32 httpUtilParseUriPath(httpUriPath *path,	const char *str, void *pool, size_t size, size_t *required);
s32 httpUtilParseProxy(httpUri *uri, const char *str, void *pool, size_t size, size_t *required);
s32 httpUtilParseStatusLine(httpStatusLine *resp, const char *str, size_t len, void *pool, size_t size,	size_t *required, size_t *parsedLength);
s32 httpUtilParseHeader(httpHeader *header,	const char *str, size_t len, void *pool, size_t size, size_t *required, size_t *parsedLength);
// builder
s32 httpUtilBuildRequestLine(const httpRequestLine *req, char *buf,	size_t len,	size_t *required);
s32 httpUtilBuildHeader(const httpHeader *header, char *buf, size_t len, size_t *required);
s32 httpUtilBuildUri(const httpUri *uri, char *buf, size_t len,	size_t *required, int32_t flags);
// copy
s32 httpUtilCopyUri(httpUri *dest, const httpUri *src, void *pool, size_t poolSize,	size_t *required);
s32 httpUtilMergeUriPath(httpUri *uri, const httpUri *src, const char *path, void *pool, size_t poolSize, size_t *required);
s32 httpUtilSweepPath(char *dst, const char *src, size_t srcSize);
s32 httpUtilCopyStatusLine(httpStatusLine *dest, const httpStatusLine *src,	void *pool,	size_t poolSize, size_t *required);
s32 httpUtilCopyHeader(httpHeader *dest, const httpHeader *src,	void *pool, size_t poolSize, size_t *required);
s32 httpUtilAppendHeaderValue(httpHeader *dest, const httpHeader *src, const char *value, void *pool, size_t poolSize, size_t *required);
// encoder
s32 httpUtilEscapeUri(char *out, size_t outSize, const unsigned char *in, size_t inSize, size_t *required);
s32 httpUtilUnescapeUri(unsigned char *out, size_t size, const char *in, size_t *required);
s32 httpUtilFormUrlEncode(char *out, size_t outSize, const unsigned char *in, size_t inSize, size_t *required);
s32 httpUtilFormUrlDecode(unsigned char *out, size_t size, const char *in, size_t *required);
s32 httpUtilBase64Encoder(char *out, const void *input,	size_t len);
s32 httpUtilBase64Decoder(char *output,	const void *in,	size_t len);

#ifdef __cplusplus
	}
#endif

#endif
