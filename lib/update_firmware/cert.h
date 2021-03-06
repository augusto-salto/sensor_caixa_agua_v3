#ifndef CERT_H

#define CERT_H
/*
const char * rootCACertificate = \
 "-----BEGIN CERTIFICATE-----\n"
"MIIFBTCCBKugAwIBAgIQAWjVdfHOhyitlajxHvFZizAKBggqhkjOPQQDAjBnMQsw\n"
"CQYDVQQGEwJVUzEXMBUGA1UEChMORGlnaUNlcnQsIEluYy4xPzA9BgNVBAMTNkRp\n"
"Z2lDZXJ0IEhpZ2ggQXNzdXJhbmNlIFRMUyBIeWJyaWQgRUNDIFNIQTI1NiAyMDIw\n"
"IENBMTAeFw0yMTAzMjUwMDAwMDBaFw0yMjAzMzAyMzU5NTlaMGgxCzAJBgNVBAYT\n"
"AlVTMRMwEQYDVQQIEwpDYWxpZm9ybmlhMRYwFAYDVQQHEw1TYW4gRnJhbmNpc2Nv\n"
"MRUwEwYDVQQKEwxHaXRIdWIsIEluYy4xFTATBgNVBAMMDCouZ2l0aHViLmNvbTBZ\n"
"MBMGByqGSM49AgEGCCqGSM49AwEHA0IABJS/f/tE4nUyACz31P7YkuqSPMwCJK1O\n"
"KaIVJXVXNG2+jtxQEZd3J6iAyvUqBeuc98Ykel7JxUvBdDsv3IV0f5GjggM2MIID\n"
"MjAfBgNVHSMEGDAWgBRQYaag0jXEESogjR8PrELwzSnPSzAdBgNVHQ4EFgQUz8sM\n"
"6+49cST4fpZacaZKm9Xcxs4wIwYDVR0RBBwwGoIMKi5naXRodWIuY29tggpnaXRo\n"
"dWIuY29tMA4GA1UdDwEB/wQEAwIHgDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYB\n"
"BQUHAwIwgbEGA1UdHwSBqTCBpjBRoE+gTYZLaHR0cDovL2NybDMuZGlnaWNlcnQu\n"
"Y29tL0RpZ2lDZXJ0SGlnaEFzc3VyYW5jZVRMU0h5YnJpZEVDQ1NIQTI1NjIwMjBD\n"
"QTEuY3JsMFGgT6BNhktodHRwOi8vY3JsNC5kaWdpY2VydC5jb20vRGlnaUNlcnRI\n"
"aWdoQXNzdXJhbmNlVExTSHlicmlkRUNDU0hBMjU2MjAyMENBMS5jcmwwPgYDVR0g\n"
"BDcwNTAzBgZngQwBAgIwKTAnBggrBgEFBQcCARYbaHR0cDovL3d3dy5kaWdpY2Vy\n"
"dC5jb20vQ1BTMIGSBggrBgEFBQcBAQSBhTCBgjAkBggrBgEFBQcwAYYYaHR0cDov\n"
"L29jc3AuZGlnaWNlcnQuY29tMFoGCCsGAQUFBzAChk5odHRwOi8vY2FjZXJ0cy5k\n"
"aWdpY2VydC5jb20vRGlnaUNlcnRIaWdoQXNzdXJhbmNlVExTSHlicmlkRUNDU0hB\n"
"MjU2MjAyMENBMS5jcnQwDAYDVR0TAQH/BAIwADCCAQMGCisGAQQB1nkCBAIEgfQE\n"
"gfEA7wB2ACl5vvCeOTkh8FZzn2Old+W+V32cYAr4+U1dJlwlXceEAAABeGq9+VQA\n"
"AAQDAEcwRQIgBMnwNQeSIIAFSuqGwFz/WKxTzcOlFgNHIOfmSXjR1/oCIQCB+snp\n"
"qYiijCUKaATYGlzpHg9zueSIYWYW2rf2gdVehAB1ACJFRQdZVSRWlj+hL/H3bYbg\n"
"IyZjrcBLf13Gg1xu4g8CAAABeGq9+a0AAAQDAEYwRAIgWw1qhWcLWzI44kbeoysV\n"
"UO0Mghm7JZKSNVUp5atZVmACIEHj26y7bFXP3/u1Ko1z7fAYYMbXb5v08/R8RKi2\n"
"7KXXMAoGCCqGSM49BAMCA0gAMEUCIQC5oZMm42S7ssfECiKBY4hvDeQ7NNpnGhRn\n"
"781tWaKFywIgIvP5KySr+oTm6PKWe4HgO7aG8LruUVfeysEIk8Pw9fY=\n"
"-----END CERTIFICATE-----\n";
*/

const char * rootCACertificate = \
  "-----BEGIN CERTIFICATE-----\n"
"MIIDxTCCAq2gAwIBAgIQAqxcJmoLQJuPC3nyrkYldzANBgkqhkiG9w0BAQUFADBs\n" \
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n" \
"d3cuZGlnaWNlcnQuY29tMSswKQYDVQQDEyJEaWdpQ2VydCBIaWdoIEFzc3VyYW5j\n" \
"ZSBFViBSb290IENBMB4XDTA2MTExMDAwMDAwMFoXDTMxMTExMDAwMDAwMFowbDEL\n" \
"MAkGA1UEBhMCVVMxFTATBgNVBAoTDERpZ2lDZXJ0IEluYzEZMBcGA1UECxMQd3d3\n" \
"LmRpZ2ljZXJ0LmNvbTErMCkGA1UEAxMiRGlnaUNlcnQgSGlnaCBBc3N1cmFuY2Ug\n" \
"RVYgUm9vdCBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMbM5XPm\n" \
"+9S75S0tMqbf5YE/yc0lSbZxKsPVlDRnogocsF9ppkCxxLeyj9CYpKlBWTrT3JTW\n" \
"PNt0OKRKzE0lgvdKpVMSOO7zSW1xkX5jtqumX8OkhPhPYlG++MXs2ziS4wblCJEM\n" \
"xChBVfvLWokVfnHoNb9Ncgk9vjo4UFt3MRuNs8ckRZqnrG0AFFoEt7oT61EKmEFB\n" \
"Ik5lYYeBQVCmeVyJ3hlKV9Uu5l0cUyx+mM0aBhakaHPQNAQTXKFx01p8VdteZOE3\n" \
"hzBWBOURtCmAEvF5OYiiAhF8J2a3iLd48soKqDirCmTCv2ZdlYTBoSUeh10aUAsg\n" \
"EsxBu24LUTi4S8sCAwEAAaNjMGEwDgYDVR0PAQH/BAQDAgGGMA8GA1UdEwEB/wQF\n" \
"MAMBAf8wHQYDVR0OBBYEFLE+w2kD+L9HAdSYJhoIAu9jZCvDMB8GA1UdIwQYMBaA\n" \
"FLE+w2kD+L9HAdSYJhoIAu9jZCvDMA0GCSqGSIb3DQEBBQUAA4IBAQAcGgaX3Nec\n" \
"nzyIZgYIVyHbIUf4KmeqvxgydkAQV8GK83rZEWWONfqe/EW1ntlMMUu4kehDLI6z\n" \
"eM7b41N5cdblIZQB2lWHmiRk9opmzN6cN82oNLFpmyPInngiK3BD41VHMWEZ71jF\n" \
"hS9OMPagMRYjyOfiZRYzy78aG6A9+MpeizGLYAiJLQwGXFK3xPkKmNEVX58Svnw2\n" \
"Yzi9RKR/5CYrCsSXaQ3pjOLAEFe4yHYSkVXySGnYvCoCWw9E1CAx2/S6cCZdkGCe\n" \
"vEsXCS+0yx5DaMkHJ8HSXPfqIbloEpw8nL+e/IBcm2PN7EeqJSdnoDfzAIJ9VNep\n" \
"+OkuE6N36B9K\n" \
"-----END CERTIFICATE-----\n";

#endif
