#
# Test how saving in a given format has changed in a new DatUtil release
#

test_regression_format()
{
	FORMAT=$1

	# --- Note: Need to use a consistent filename (e.g. test.0) for formats such as delimited ---

	if [[ "$TEST_OPTION" = "" ]]
	then
		printf "Checking regression for '$FORMAT' format (using '$DATA_FILE')... "
	else
		printf "Checking regression for '$FORMAT' format with $TEST_OPTION (using '$DATA_FILE')... "
	fi

	cp "$DATA_FILE" "test.0"
	$LOGIQX/bin/datutil $DATA_OPTION $TEST_OPTION -f $FORMAT -o "test.1" "test.0" >/dev/null

	cp "$DATA_FILE" "test.0"
	$LOGIQX/dev/datutil/datutil $DATA_OPTION $TEST_OPTION -f $FORMAT -o "test.2" "test.0" >/dev/null

	if [[ "$(diff test.1 test.2)" != "" ]]
	then
		echo "difference!"
		csdiff test.1 test.2
	else
		echo "ok!"
	fi

	# --- Cleanup ---

	rm -f test.[0-9]
}

test_regression()
{
	TEST_OPTION=$1

	test_regression_format listinfo
	test_regression_format listxml
	test_regression_format delimited
	test_regression_format romcenter
}

#
# Test that loading and saving is consistent for a given format
#

test_load_save_format()
{
	FORMAT=$1

	# --- Note: Need to use a consistent filename (e.g. test.0) for formats such as delimited ---

	if [[ "$TEST_OPTION" = "" ]]
	then
		printf "Checking load/save consistency for '$FORMAT' format (using '$DATA_FILE')... "
	else
		printf "Checking load/save consistency for '$FORMAT' format with $TEST_OPTION (using '$DATA_FILE')... "
	fi

	cp "$DATA_FILE" "test.0"
	$LOGIQX/dev/datutil/datutil $DATA_OPTION $TEST_OPTION -f $FORMAT -o "test.1" "test.0" >/dev/null

	cp "test.1" "test.0"
	$LOGIQX/dev/datutil/datutil $DATA_OPTION $TEST_OPTION -f $FORMAT -o "test.2" "test.0" >/dev/null

	if [[ "$(diff test.1 test.2)" != "" ]]
	then
		echo "difference!"
		csdiff test.1 test.2
	else
		echo "ok!"
	fi

	# --- Cleanup ---

	rm -f test.[0-9]
}

test_load_save()
{
	TEST_OPTION=$1

	test_load_save_format listinfo
	test_load_save_format listxml
	test_load_save_format delimited
	test_load_save_format romcenter
}

#
# Test that cycling through all of the full load/save formats results in an unchanging file
#

test_cycle()
{
	TEST_OPTION=$1

	if [[ "$TEST_OPTION" = "" ]]
	then
		printf "Checking cyclic conversion (using '$DATA_FILE')... "
	else
		printf "Checking cyclic conversion with $TEST_OPTION (using '$DATA_FILE')... "
	fi

	FAILED=0

	# --- Convert to ListInfo ---

	printf "1 "

	if (( $FAILED == 0 ))
	then
		cp "$DATA_FILE" "test.0"
		$LOGIQX/dev/datutil/datutil $DATA_OPTION $TEST_OPTION -f listinfo -o "test.1" "test.0" >/dev/null

		cp "test.1" "test.0"
		$LOGIQX/dev/datutil/datutil $DATA_OPTION $TEST_OPTION -f listinfo -o "test.2" "test.0" >/dev/null

		if [[ "$(diff test.1 test.2)" != "" ]]
		then
			echo "difference!"
			csdiff test.1 test.2
			FAILED=1
		fi
	fi

	# --- Convert to ListXML ---

	printf "2 "

	if (( $FAILED == 0 ))
	then
		cp "$DATA_FILE" "test.0"
		$LOGIQX/dev/datutil/datutil $DATA_OPTION $TEST_OPTION -f listxml -o "test.1" "test.0" >/dev/null

		cp "test.2" "test.0"
		$LOGIQX/dev/datutil/datutil $DATA_OPTION $TEST_OPTION -f listxml -o "test.2" "test.0" >/dev/null

		if [[ "$(diff test.1 test.2)" != "" ]]
		then
			echo "difference!"
			csdiff test.1 test.2
			FAILED=1
		fi
	fi

	# --- Convert to Delimited ---

	printf "3 "

	if (( $FAILED == 0 ))
	then
		cp "$DATA_FILE" "test.0"
		$LOGIQX/dev/datutil/datutil $DATA_OPTION $TEST_OPTION -f delimited -o "test.1" "test.0" >/dev/null

		cp "test.2" "test.0"
		$LOGIQX/dev/datutil/datutil $DATA_OPTION $TEST_OPTION -f delimited -o "test.2" "test.0" >/dev/null

		if [[ "$(diff test.1 test.2)" != "" ]]
		then
			echo "difference!"
			csdiff test.1 test.2
			FAILED=1
		fi
	fi

	# --- Convert to ListInfo ---

	printf "4 "

	if (( $FAILED == 0 ))
	then
		cp "$DATA_FILE" "test.0"
		$LOGIQX/dev/datutil/datutil $DATA_OPTION $TEST_OPTION -f listinfo -o "test.1" "test.0" >/dev/null

		cp "test.2" "test.0"
		$LOGIQX/dev/datutil/datutil $DATA_OPTION $TEST_OPTION -f listinfo -o "test.2" "test.0" >/dev/null

		if [[ "$(diff test.1 test.2)" != "" ]]
		then
			echo "difference!"
			csdiff test.1 test.2
			FAILED=1
		fi
	fi

	# --- Done ---

	if (( $FAILED == 0 ))
	then
		echo "ok!"
	fi

	# --- Cleanup ---

	rm -f test.[0-9]
}

#
# The command line interface
#

unset DATA_FILE
unset DATA_OPTION

case "$1" in
	fba)
		DATA_FILE="FB Alpha v0.2.96.77 (ClrMame Pro).dat"
		;;
	m1)
		DATA_FILE="m1.xml"
		;;
	nebula)
		DATA_FILE="NEOGEO.DAT"
		;;
	nebulajb)
		DATA_FILE="NEOGEO.DAT"
		DATA_OPTION=-j
		;;
	raine)
		DATA_FILE="RAINE Listinfo.dat"
		;;
	mame)
		DATA_FILE="mame.xml"
		;;
	mess)
		DATA_FILE="mess.xml"
		;;
	*)
		echo "Error: Unrecognised test file '$1'"
		;;
esac

if [[ "$DATA_FILE" != "" ]]
then
	test_regression
	test_regression -k
	test_load_save
	test_load_save -k
	test_cycle
	test_cycle -k
fi

rm -f datutil.log
