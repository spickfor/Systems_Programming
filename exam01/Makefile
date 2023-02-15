test:
	@$(MAKE) -sk test-all

test-all:	test-scripts test-filters

test-scripts:
	curl -sL https://yld.me/raw/gOW8 > test_filters.sh
	chmod +x test_filters.sh

test-filters:
	./test_filters.sh
