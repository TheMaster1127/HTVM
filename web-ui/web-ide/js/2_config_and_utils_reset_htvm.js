function resetGlobalVarsOfHTVMjs() {
    str0 = "nothing";
    str00 = "nothing";
    str1 = "";
    str2 = "";
    str3 = "";
    str4 = "";
    str5 = "";
    str6 = "";
    str7 = "";
    str8 = "";
    str9 = "";
    str10 = "";
    str11 = "";
    str12 = "";
    str13 = "";
    str14 = "";
    str15 = "";
    str16 = "";
    str17 = "";
    str18 = "";
    str19 = "";
    str20 = "";
    str21 = "";
    int0 = 0;
    int1 = 0;
    int2 = 0;
    int3 = 0;
    int4 = 0;
    int5 = 0;
    int6 = 0;
    int7 = 0;
    argHTVMinstrMORE = [];
    isNotHTVMfileEXTRA_INT = 0;
    isNotHTVMfile2 = 0;
    isNotHTVMfileEXTRA_LIB_INFO = "";
    isNotHTVMfileEXTRA_FUNCS_INFO = "";
    programmingBlock_InTheTranspiledLang = [];
    programmingBlock_CPP = [];
    programmingBlock_PY = [];
    programmingBlock_JS = [];
    programmingBlock_GO = [];
    programmingBlock_LUA = [];
    programmingBlock_CS = [];
    programmingBlock_JAVA = [];
    programmingBlock_KT = [];
    programmingBlock_RB = [];
    programmingBlock_NIM = [];
    programmingBlock_AHK = [];
    programmingBlock_SWIFT = [];
    programmingBlock_DART = [];
    programmingBlock_TS = [];
    programmingBlock_GROOVY = [];
    programmingBlock_HTVM = [];
    programmingBlock_HTVMsyntax = [];
    fullLangAllOperators = [];
    fullLangAllOperators_HELP = [];
    fixExpertionLineFuncOnly = 0;
    langToConvertTo = "";
    langFileExtension = "";
    commands = "";
    keyWordAlliance = "";
    keyWordCrew = "";
    keyWordProc = "";
    keyWordStruct = "";
    keyWordProp = "";
    keyWordThis = "";
    keyWordInclude = "";
    keyWordCodeInTheTranspiledLangStart = "";
    keyWordCodeInTheTranspiledLangEnd = "";
    keyWordCodeInTheTranspiledLangStartCPP = "";
    keyWordCodeInTheTranspiledLangEndCPP = "";
    keyWordCodeInTheTranspiledLangStartPY = "";
    keyWordCodeInTheTranspiledLangEndPY = "";
    keyWordCodeInTheTranspiledLangStartJS = "";
    keyWordCodeInTheTranspiledLangEndJS = "";
    keyWordCodeInTheTranspiledLangStartGO = "";
    keyWordCodeInTheTranspiledLangEndGO = "";
    keyWordCodeInTheTranspiledLangStartLUA = "";
    keyWordCodeInTheTranspiledLangEndLUA = "";
    keyWordCodeInTheTranspiledLangStartCS = "";
    keyWordCodeInTheTranspiledLangEndCS = "";
    keyWordCodeInTheTranspiledLangStartJAVA = "";
    keyWordCodeInTheTranspiledLangEndJAVA = "";
    keyWordCodeInTheTranspiledLangStartKT = "";
    keyWordCodeInTheTranspiledLangEndKT = "";
    keyWordCodeInTheTranspiledLangStartRB = "";
    keyWordCodeInTheTranspiledLangEndRB = "";
    keyWordCodeInTheTranspiledLangStartNIM = "";
    keyWordCodeInTheTranspiledLangEndNIM = "";
    keyWordCodeInTheTranspiledLangStartAHK = "";
    keyWordCodeInTheTranspiledLangEndAHK = "";
    keyWordCodeInTheTranspiledLangStartSWIFT = "";
    keyWordCodeInTheTranspiledLangEndSWIFT = "";
    keyWordCodeInTheTranspiledLangStartDART = "";
    keyWordCodeInTheTranspiledLangEndDART = "";
    keyWordCodeInTheTranspiledLangStartTS = "";
    keyWordCodeInTheTranspiledLangEndTS = "";
    keyWordCodeInTheTranspiledLangStartGROOVY = "";
    keyWordCodeInTheTranspiledLangEndGROOVY = "";
    keyWordCodeInTheTranspiledLangStartHTVM = "";
    keyWordCodeInTheTranspiledLangEndHTVM = "";
    keyWordCodeInHTVMstart = "";
    keyWordCodeInHTVMend = "";
    keyWordCurlyBraceOpen = "";
    keyWordCurlyBraceClose = "";
    keyWordNull = "";
    keyWordTrue = "";
    keyWordFalse = "";
    keyWordVoid = "";
    keyWordDouble = "";
    keyWordChar = "";
    keyWordUint8 = "";
    keyWordUint16 = "";
    keyWordUint32 = "";
    keyWordUint64 = "";
    keyWordINT = "";
    keyWordSTR = "";
    keyWordBOOL = "";
    keyWordFLOAT = "";
    keyWordINT8 = "";
    keyWordINT16 = "";
    keyWordINT32 = "";
    keyWordINT64 = "";
    keyWordIF = "";
    keyWordElseIf = "";
    keyWordElse = "";
    keyWordWhileLoop = "";
    keyWordLoopInfinite = "";
    keyWordLoop = "";
    keyWordLoopParse = "";
    keyWordContinue = "";
    keyWordBreak = "";
    keyWordFunc = "";
    keyWordAwait = "";
    keyWordAsync = "";
    keyWordThrow = "";
    keyWordErrorMsg = "";
    keyWordTry = "";
    keyWordCatch = "";
    keyWordFinally = "";
    keyWordReturnStatement = "";
    keyWordArrayAppend = "";
    keyWordArrayPop = "";
    keyWordArraySize = "";
    keyWordArrayInsert = "";
    keyWordArrayRemove = "";
    keyWordArrayIndexOf = "";
    keyWordArrayDefinition = "";
    keyWordArrayOfIntegersDefinition = "";
    keyWordArrayOfStringsDefinition = "";
    keyWordArrayOfFloatingPointNumbersDefinition = "";
    keyWordArrayOfBooleansDefinition = "";
    keyWordVar = "";
    keyWordLet = "";
    keyWordConst = "";
    keyWordEnd = "";
    keyWordGlobal = "";
    keyWordComment = "";
    keyWordCommentOpenMultiLine = "";
    keyWordCommentCloseMultiLine = "";
    keyWordEscpaeChar = "";
    keyWordMainLabel = "";
    keyWordConcat = "";
    keyWordAdd = "";
    keyWordSub = "";
    keyWordMul = "";
    keyWordDiv = "";
    keyWordMod = "";
    keyWordExp = "";
    keyWordEqual = "";
    keyWordStrictEqual = "";
    keyWordNotEqual = "";
    keyWordGreater = "";
    keyWordLess = "";
    keyWordGreaterEqual = "";
    keyWordLessEqual = "";
    keyWordAnd = "";
    keyWordOr = "";
    keyWordNot = "";
    keyWordBitAnd = "";
    keyWordBitOr = "";
    keyWordBitXor = "";
    keyWordBitNot = "";
    keyWordShiftLeft = "";
    keyWordShiftRight = "";
    keyWordShiftUnsignedRight = "";
    keyWordAssign = "";
    keyWordAssignAdd = "";
    keyWordAssignConcat = "";
    keyWordAssignSub = "";
    keyWordAssignMul = "";
    keyWordAssignDiv = "";
    keyWordAssignMod = "";
    keyWordAssignShiftLeft = "";
    keyWordAssignShiftRight = "";
    keyWordLogicalAssignShiftRight = "";
    keyWordAssignBitAnd = "";
    keyWordAssignBitOr = "";
    keyWordAssignBitXor = "";
    keyWordTernary1 = "";
    keyWordTernary2 = "";
    keyWordInc = "";
    keyWordDec = "";
    AHKlikeLoopsIndexedAt = "";
    keyWordAIndex = "";
    keyWordALoopField = "";
    useFuncKeyWord = "";
    useCurlyBraces = "";
    useEnd = "";
    useSemicolon = "";
    theSemicolon = "";
    theColon = "";
    useParentheses = "";
    usePrefixTypeForTypeDefinition = "";
    usePostfixTypeForTypeDefinition = "";
    usePythonicColonSyntax = "";
    useCurlyBracesSyntaxForArrayDef = "";
    useInJavaScriptAlwaysUseVar = "";
    useJavaScriptInAfullHTMLfile = "";
    useJavaScriptAmainFuncDef = "";
    useJavaScriptAllFuncsAreAsync = "";
    useJavaScriptAlwaysTripleEqual = "";
    langToConvertTo_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    langFileExtension_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    commands_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAlliance_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCrew_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordProc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordStruct_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordProp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordThis_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordInclude_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartCPP_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndCPP_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartPY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndPY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartJS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndJS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartGO_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndGO_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartLUA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndLUA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartCS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndCS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartJAVA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndJAVA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartKT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndKT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartRB_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndRB_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartNIM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndNIM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartAHK_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndAHK_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartSWIFT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndSWIFT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartDART_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndDART_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartTS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndTS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangStartHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInTheTranspiledLangEndHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInHTVMstart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCodeInHTVMend_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCurlyBraceOpen_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCurlyBraceClose_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordNull_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordTrue_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordFalse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordVoid_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordDouble_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordChar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordUint8_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordUint16_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordUint32_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordUint64_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordINT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordSTR_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordBOOL_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordFLOAT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordINT8_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordINT16_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordINT32_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordINT64_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordIF_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordElseIf_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordElse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordWhileLoop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordLoopInfinite_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordLoop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordLoopParse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordContinue_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordBreak_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordFunc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAwait_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAsync_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordThrow_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordErrorMsg_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordTry_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCatch_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordFinally_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordReturnStatement_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordArrayAppend_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordArrayPop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordArraySize_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordArrayInsert_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordArrayRemove_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordArrayIndexOf_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordArrayDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordArrayOfIntegersDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordArrayOfStringsDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordArrayOfFloatingPointNumbersDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordArrayOfBooleansDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordVar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordLet_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordConst_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordGlobal_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordComment_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCommentOpenMultiLine_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordCommentCloseMultiLine_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordEscpaeChar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordMainLabel_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordConcat_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAdd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordSub_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordMul_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordDiv_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordMod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordExp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordStrictEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordNotEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordGreater_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordLess_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordGreaterEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordLessEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordNot_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordBitAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordBitOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordBitXor_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordBitNot_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordShiftLeft_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordShiftUnsignedRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssign_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssignAdd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssignConcat_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssignSub_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssignMul_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssignDiv_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssignMod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssignShiftLeft_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssignShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordLogicalAssignShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssignBitAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssignBitOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAssignBitXor_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordTernary1_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordTernary2_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordInc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordDec_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    AHKlikeLoopsIndexedAt_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordAIndex_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordALoopField_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    useCurlyBraces_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    useEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    useSemicolon_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    useParentheses_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    usePrefixTypeForTypeDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    usePostfixTypeForTypeDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    usePythonicColonSyntax_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    useCurlyBracesSyntaxForArrayDef_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    useInJavaScriptAlwaysUseVar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    useJavaScriptInAfullHTMLfile_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    useJavaScriptAmainFuncDef_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    useJavaScriptAllFuncsAreAsync_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    useJavaScriptAlwaysTripleEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
    keyWordALoopFieldOriginal = "";
    keyWordAIndexOriginal = "";
    out_KeyWordsCommands = "";
    outTrimCode = "";
    htCode = "";
    outVarOperator = "";
    lineDone = 0;
    areWeInAFuncFromInstructions = 0;
    areWeInAFuncFromInstructionsLineNum = 0;
    javaMainFuncSeen = 0;
    csMainFuncSeen = 0;
    howMany_fixAindexInGoUnused = 0;
    luaContinueFix_Num = 0;
    theTryCatchVarForErrors = "jhku-dfsds-ds-d-ffdsf-sdfsfdsedsf";
    allVarsSoWeDontReDecVars = [];
    allVarsSoWeDontReDecVars_FIX_uint8 = [];
    allVarsSoWeDontReDecVars_FIX_uint16 = [];
    allVarsSoWeDontReDecVars_FIX_uint32 = [];
    allVarsSoWeDontReDecVars_FIX_uint64 = [];
    allVarsSoWeDontReDecVars_FIX_int64 = [];
    allVarsSoWeDontReDecVars_FIX_float = [];
    allVarsSoWeDontReDecVars_FIX_TOGGLE = 0;
    availableFuncsInHTVMInHTVM = "";
    saveAllArrayVarNamesSoWeCanDoAfix = "|";
    initializeBackendAndGUIInteractionWithLabelSubroutineLikeButConvertsToFunction_WAS_IN_PYTHON = 0;
    weAreInMLSarr = [];
    ospDic = [];
    ospDic1 = [];
    ospDic2 = [];
}