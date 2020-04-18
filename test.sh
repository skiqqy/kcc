### This is used to run all tests for TravisCL ###
### Please use `make test` for desired results  ###
echo "Beggining unit tests"

### Test the scanner  ###
echo "Testing scanner"
for f in tests/scanner/*
do
	echo "./bin/testscanner $f"
	./bin/testscanner $f
done
#########################
