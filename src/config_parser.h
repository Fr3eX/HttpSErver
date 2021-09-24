#ifndef CONFIG_PARSER
#define CONFIG_PARSER


void __ParseCfgFile(char const*);
void* __Get(char const*);
void __FreePData(void);
char* getConfigFilename();


#endif
