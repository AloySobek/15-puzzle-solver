for i in {1..50000}
do
  python2 $2 -s -i ${RANDOM:0:5} ${RANDOM:0:2} > ./test
  echo NUM: $i
  $1 -p ./test | grep -q "is not solvable!"; [[ $? -eq 1 ]] || {
    cat ./test;
    echo >&2 "__ERROR__";
    exit 1;
  }
done
