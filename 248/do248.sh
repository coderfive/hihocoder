
while : ; do
	python3 gen248.py
	./248 <in > o2 &
	pid=$!
	sleep 2
	if [ -e /proc/$pid ]; then
		kill $pid
		echo "found LTE example"
		break
	fi
	cmp o2 out
	if [ $? -ne 0 ]; then
		echo "found incorrect answer example"
		break
	fi
done
