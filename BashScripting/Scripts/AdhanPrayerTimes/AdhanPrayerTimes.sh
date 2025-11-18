#! /bin/bash

function json_parser_usingpython()
{
    res=` curl "http://api.aladhan.com/v1/timingsByCity/18-11-2025?city=Giza&country=Egypt" | json_pp -f json`
    export json_file="$res"
    python3 -c "import os,json; x=os.environ['json_file'] ;
# print(x)    # x is string 
body=json.loads(x)['data']['timings']
# print(body)
for i,j, in  body.items():
    print (i,j)
    "
}


function json_parser_usingBash()
{
    res=` curl "http://api.aladhan.com/v1/timingsByCity/18-11-2025?city=Giza&country=Egypt" | json_pp -f json`
    # echo ${res} | jq . 
    # echo ${res} | jq '.code'
    echo ${res} | jq '.data.timings'
}

# json_parser_usingpython
json_parser_usingBash

