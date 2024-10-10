# Benchmark results Results for Encoding


[The latest results are here](https://rawcdn.githack.com/gaspardpetit/base64/main/result/result.html)

# base64

Searching the web for a C/C++ base64 implementation yields many results.
 
 
How does one chose?
This project aims at collecting and comparing the different implementations available.
 
Feel free to improve this test or to submit new implementations! 

### Disclaimer

Keep in mind that some implementations were slightly modified to have a common interface for the test framework.  In all cases, line breaks were omitted both for encoding and parsing. Also, although all implementations have been unit-tested, no analysis whatsoever has been made on error handling, so some slower implementation may actually be better at reporting malformed base64 strings for instance.

I do not own any of these implementations - make sure you check their respective license before using them.

## Compared implementations

### base64 (Alfred Klomp)
From https://github.com/aklomp/base64
A fast C99 implementation with SIMD acceleration 

### base64 (Tobias Locker)
From https://github.com/tobiaslocker/base64
A c++ single-header library implementing the approach of Nick Galbreath's in  `modp_b64`

### base64 (Mat Gomes)
From https://github.com/matheusgomes28/base64pp
A c++ library written for readibility and supported by a blog post https://matgomes.com/base64-encode-decode-cpp/

### adp-gmbh (René Nyffenegger)
From http://www.adp-gmbh.ch/cpp/common/base64.html

### lib64
From https://sourceforge.net/projects/libb64/
 
### libcurl
From https://curl.haxx.se/libcurl/
 
### Internet Software Consortium
From https://opensource.apple.com/source/basic_cmds/basic_cmds-55/uuencode/base64.c
 
### Arduino-Base64
From https://github.com/adamvr/arduino-base64 from BuLogic's fork (https://github.com/BuLogics/libb64)
 
### LihO
From stackoverflow thread at http://stackoverflow.com/questions/180947/base64-decode-snippet-in-c

### Manuel Martinez
From stackoverflow thread at http://stackoverflow.com/questions/180947/base64-decode-snippet-in-c

### DaedalusAlpha
From stackoverflow thread at http://stackoverflow.com/questions/180947/base64-decode-snippet-in-c

### Elegant Dice
From stackoverflow thread at http://stackoverflow.com/questions/180947/base64-decode-snippet-in-c
 
### polfosol
From stackoverflow thread at http://stackoverflow.com/questions/180947/base64-decode-snippet-in-c

### omnifarious
From stackoverflow thread at http://stackoverflow.com/questions/5288076/doing-base64-encoding-and-decoding-in-openssl-c

** Note that although this implementation is in the results, it does not produce valid results - including extra '=' padding when not necessary.

### user152949
From stackoverflow thread at http://stackoverflow.com/questions/180947/base64-decode-snippet-in-c

### jounimalinen
From http://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c

### test_wikibooks_org_c
From https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64

### test_wikibooks_org_cpp
From https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64

### apache
Which I think was based on Rob McCool's uuencode's implementation in 1993
https://opensource.apple.com/source/QuickTimeStreamingServer/QuickTimeStreamingServer-452/CommonUtilitiesLib/base64.c

### NibbleAndAHalf
From https://github.com/superwills/NibbleAndAHalf/

### Gnome
From https://github.com/GNOME/glib/blob/master/glib/gbase64.c

### cppcodec
From https://github.com/tplgy/cppcodec

## Conclusion

- If you want the fastest implementation, go for base64 (Alfred Klomp) noting that the code base is BSD-2
- If you want a simple single-header c++ file with good performance, go for base64 (Tobias Locker)
- Some other implementations are terrible, the slower ones generally allocate memory dynamically as they convert, even though the output size is deterministic and can be preallocated;
- libb64 shows very strange performance results - I get the feeling that they are doing something neat but that I am perhaps not using their code right;
- A lot of implementations are available, everyone claims theirs is better. This test shows that unless you measure, you cannot make any claims about the performance of your code;

Keep in mind that these results were all obtained using Visual Studio and could differ on another compiler.
