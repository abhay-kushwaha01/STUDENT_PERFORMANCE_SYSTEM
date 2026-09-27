#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int safe_copy(char *dst, size_t dst_size, const char *src) {
    if (!dst || dst_size == 0 || !src) return 0;
    size_t n = strlen(src);
    if (n >= dst_size) n = dst_size - 1;
    memcpy(dst, src, n); dst[n] = '\0'; return 1;
}
void trim_newline(char *s) { if (!s) return; size_t n=strlen(s); while(n && (s[n-1]=='\n'||s[n-1]=='\r')) s[--n]='\0'; }
static int hexv(char c){ if(c>='0'&&c<='9')return c-'0'; if(c>='a'&&c<='f')return c-'a'+10; if(c>='A'&&c<='F')return c-'A'+10; return -1; }
void url_decode(char *dst,size_t sz,const char *src){ size_t o=0; for(size_t i=0;src&&src[i]&&o+1<sz;i++){ if(src[i]=='%'&&src[i+1]&&src[i+2]){int a=hexv(src[i+1]),b=hexv(src[i+2]); if(a>=0&&b>=0){dst[o++]=(char)(a*16+b);i+=2;continue;}} if(src[i]=='+')dst[o++]=' '; else dst[o++]=src[i];} if(sz)dst[o]='\0'; }
int url_encode(char *dst,size_t sz,const char *src){ const char *h="0123456789ABCDEF"; size_t o=0; for(size_t i=0;src&&src[i];i++){ unsigned char c=(unsigned char)src[i]; if(isalnum(c)||c=='-'||c=='_'||c=='.'||c=='~'){if(o+1>=sz)return 0;dst[o++]=c;}else{if(o+3>=sz)return 0;dst[o++]='%';dst[o++]=h[c>>4];dst[o++]=h[c&15];}} if(sz)dst[o]='\0'; return 1; }
int json_escape(char *dst,size_t sz,const char *src){ size_t o=0; for(size_t i=0;src&&src[i];i++){ const char *rep=NULL; char tmp[8]; unsigned char c=(unsigned char)src[i]; if(c=='"')rep="\\\""; else if(c=='\\')rep="\\\\"; else if(c=='\n')rep="\\n"; else if(c=='\r')rep="\\r"; else if(c=='\t')rep="\\t"; else if(c<32){snprintf(tmp,sizeof(tmp),"\\u%04x",c);rep=tmp;} if(rep){size_t n=strlen(rep);if(o+n>=sz)return 0;memcpy(dst+o,rep,n);o+=n;}else{if(o+1>=sz)return 0;dst[o++]=c;}} if(sz)dst[o]='\0';return 1; }
static const char *find_key(const char *j,const char *key){ char k[128]; snprintf(k,sizeof(k),"\"%s\"",key); return j?strstr(j,k):NULL; }
const char *json_get_string(const char *json,const char *key,char *out,size_t out_size){ const char*p=find_key(json,key); if(!p)return NULL; p=strchr(p,':'); if(!p)return NULL; p++;while(*p&&isspace((unsigned char)*p))p++;if(*p!='"')return NULL;p++;size_t o=0;while(*p&&*p!='"'&&o+1<out_size){if(*p=='\\'&&p[1]){p++;if(*p=='n')out[o++]='\n';else if(*p=='r')out[o++]='\r';else if(*p=='t')out[o++]='\t';else out[o++]=*p;}else out[o++]=*p;p++;}if(*p!='"')return NULL;out[o]='\0';return out;}
int json_get_int(const char *json,const char *key,int*out){char tmp[64];if(!json_get_string(json,key,tmp,sizeof(tmp))){const char*p=find_key(json,key);if(!p)return 0;p=strchr(p,':');if(!p)return 0;p++;while(*p&&isspace((unsigned char)*p))p++;char*e=NULL;long v=strtol(p,&e,10);if(e==p)return 0;*out=(int)v;return 1;}*out=atoi(tmp);return 1;}
void now_string(char*out,size_t sz){time_t t=time(NULL);struct tm*tmv=localtime(&t);if(tmv)strftime(out,sz,"%Y-%m-%d %H:%M:%S",tmv);else safe_copy(out,sz,"unknown");}
int is_number_range(const char*s,double min,double max){if(!s||!*s)return 0;char*e=NULL;double v=strtod(s,&e);while(e&&*e&&isspace((unsigned char)*e))e++;return e&&*e=='\0'&&v>=min&&v<=max;}
