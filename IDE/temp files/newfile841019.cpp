#include <algorithm>
#include <any>
#include <cstdint>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

// Function to get input from the user, similar to Python's input() function
std::string input(const std::string& prompt) {
    std::string userInput;
    std::cout << prompt; // Display the prompt to the user
    std::getline(std::cin, userInput); // Get the entire line of input
    return userInput;
}

std::string Trim(const std::string &inputString) {
    if (inputString.empty()) return "";
    size_t start = inputString.find_first_not_of(" \t\n\r\f\v");
    size_t end = inputString.find_last_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : inputString.substr(start, end - start + 1);
}

std::string StringTrimRight(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(0, input.length() - numChars) : input;
}

std::string Chr(int number) {
    return (number >= 0 && number <= 0x10FFFF) ? std::string(1, static_cast<char>(number)) : "";
}


int main(int argc, char* argv[]) {
    input := "cpp`nhtvm`nStringTrimLeft,OUTVAR,INVAR,param1|StringTrimRight,OUTVAR,INVAR,param1|Random,OUTVAR,param1,param2|Sleep,INVAR|FileRead,OUTVAR,'param1|FileAppend,INVAR,'param1|FileDelete,'INVAR|Sort,INOUTVAR,'param1|MsgBox,'param1`nalliance`ncrew`nmethod`ndef obj`nporp`nthis`nimport`nkeyWordCodeInTheTranspiledLangStart`nkeyWordCodeInTheTranspiledLangEnd`nkeyWordCodeInTheTranspiledLangStartCPP`nkeyWordCodeInTheTranspiledLangEndCPP`nkeyWordCodeInTheTranspiledLangStartPY`nkeyWordCodeInTheTranspiledLangEndPY`n[js start]`n[js end]`nkeyWordCodeInTheTranspiledLangStartGO`nkeyWordCodeInTheTranspiledLangEndGO`nkeyWordCodeInTheTranspiledLangStartLUA`nkeyWordCodeInTheTranspiledLangEndLUA`nkeyWordCodeInTheTranspiledLangStartCS`nkeyWordCodeInTheTranspiledLangEndCS`nkeyWordCodeInTheTranspiledLangStartJAVA`nkeyWordCodeInTheTranspiledLangEndJAVA`nkeyWordCodeInTheTranspiledLangStartKT`nkeyWordCodeInTheTranspiledLangEndKT`nkeyWordCodeInTheTranspiledLangStartRB`nkeyWordCodeInTheTranspiledLangEndRB`nkeyWordCodeInTheTranspiledLangStartNIM`nkeyWordCodeInTheTranspiledLangEndNIM`nkeyWordCodeInTheTranspiledLangStartAHK`nkeyWordCodeInTheTranspiledLangEndAHK`nkeyWordCodeInTheTranspiledLangStartSWIFT`nkeyWordCodeInTheTranspiledLangEndSWIFT`nkeyWordCodeInTheTranspiledLangStartDART`nkeyWordCodeInTheTranspiledLangEndDART`nkeyWordCodeInTheTranspiledLangStartTS`nkeyWordCodeInTheTranspiledLangEndTS`nkeyWordCodeInTheTranspiledLangStartGROOVY`nkeyWordCodeInTheTranspiledLangEndGROOVY`nkeyWordCodeInTheTranspiledLangStartHTVM`nkeyWordCodeInTheTranspiledLangEndHTVM`nkeyWordCodeInHTVMstart`nkeyWordCodeInHTVMend`n{`n}`nnull`ntrue`nfalse`nvoid`ndouble`nchar`nuint8`nuint16`nuint32`nuint64`nint`nstr`nbool`nfloat`nint8`nint16`nint32`nint64`nif`nelse if`nelse`nwhile`nLoop`nLoop,`nLoop, Parse,`ncontinue`nbreak`nfunc`nawait`nasync`nthrow`nErrorMsg`ntry`ncatch`nfinally`nreturn`n.add`n.pop`n.size`n.insert`n.rm`n.indexOf`narr`narr int`narr str`narr float`narr bool`nvar`nlet`nconst`nend`nglobal`n;`n'''1`n'''2`n" . Chr(96) . "`nmain`n.`n+`n-`n*`n/`n%`n**`n=`n===`n!=`n" . Chr(62) . "`n" . Chr(60) . "`n" . Chr(62) . "=`n" . Chr(60) . "=`nand`nor`n!`n&`n|`n^`n~`n" . Chr(60) . "" . Chr(60) . "`n" . Chr(62) . "" . Chr(62) . "`n" . Chr(62) . "" . Chr(62) . "" . Chr(62) . "`n:=`n+=`n.=`n-=`n*=`n/=`n%=`n" . Chr(60) . "" . Chr(60) . "=`n" . Chr(62) . "" . Chr(62) . "=`n" . Chr(62) . "" . Chr(62) . "" . Chr(62) . "=`n&=`n|=`n^=`n?`n:`n++`n--`n0`nA_Index`nA_LoopField`non`noff`noff`non`non`noff`noff`noff`non`noff`noff`non`noff"
    out := ""
    Loop, Parse, input, `n, `r {
        out .= A_Index . ": " . A_LoopField . Chr(10);
    }
    out = StringTrimRight(out, 1);
    Clipboard := out
    return 0;
}