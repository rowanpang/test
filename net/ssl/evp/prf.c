#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/evp.h>
#include<openssl/hmac.h>

int prf_tls12(unsigned char* key,unsigned char *seed,char seedlen,
	unsigned char *out,char outlen)
{
    int ret = 0;

    int outTmpLen = 0;
    unsigned char *outTmp;

    unsigned char seedTmp[EVP_MAX_MD_SIZE*2];
    char seedTmpLen;
    unsigned int hlen_Ai,hlen_AiPlusSeed;
    unsigned char *hret;
    unsigned char hret_Ai[EVP_MAX_MD_SIZE];
	/*for HMAC return point to static arrary,so
	 * the second hmac will overwrite the first one,so
	 * we need one to backup.*/

    outTmp = malloc(outlen+EVP_MAX_MD_SIZE);
    memset(outTmp,0,outlen);

    seedTmpLen = (seedlen < EVP_MAX_MD_SIZE) ? seedlen : EVP_MAX_MD_SIZE;
    memcpy(seedTmp,seed,seedTmpLen);
    while(1){
	/*hret是A(1)*/
	hret = HMAC(EVP_sha256(),key,strlen((char*)key),
			seedTmp,seedTmpLen,hret_Ai,&hlen_Ai);

	memcpy(seedTmp,hret_Ai,hlen_Ai);
	memcpy(seedTmp+hlen_Ai,seed,seedlen);
	seedTmpLen =hlen_Ai + seedlen;

	/*hret是hmac(A(1)+seed)*/
	hret = HMAC(EVP_sha256(),key,strlen((char*)key),
				seedTmp,seedTmpLen,NULL,&hlen_AiPlusSeed);

	memcpy(outTmp+outTmpLen,hret,hlen_AiPlusSeed);
	outTmpLen += hlen_AiPlusSeed;
	if( outTmpLen >= outlen){
	    break;
	}

	memcpy(seedTmp,hret_Ai,hlen_Ai);
	seedTmpLen = hlen_Ai;

	/*printf("seedTmp:\n");*/
	/*for(int i=0; i<seedTmpLen; i++){*/
	    /*printf("%02x ",seedTmp[i]);*/
	    /*if (i && ((i+1)&0xf) == 0){*/
		/*printf("\n");*/
	    /*}*/
	/*}*/

    }

    printf("len need:%d,gen:%d\n",outlen,outTmpLen);

    memcpy(out,outTmp,outlen);
    free(outTmp);

    return ret;
}

int main(int argc,char** argv)
{
    int ret;
    char *key = "keyforhmac";
    char *msg = "msg-for-hmac-sha256";

    int kdLen = 61;
    unsigned char *kd;

    if (argc > 1){
	kdLen = atoi(argv[1]);
    }

    kd = malloc(kdLen);
    printf("max hash size in byt:%d\n",EVP_MAX_MD_SIZE);

    ret = prf_tls12((unsigned char*)key,(unsigned char*)msg,strlen(msg),kd,kdLen);

    printf("key derivatioin:\n");
    for(int i=0; i<kdLen; i++){
	printf("%02x ",kd[i]);
	if (i && ((i+1)&0xf) == 0){
	    printf("\n");
	}
    }

    free(kd);
    ret = 0;
    return ret;
}
