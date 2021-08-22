
function err(t) {
	print t >> "/dev/stderr"
	exit(1)
}

/\/\/ -------------- >8/ {
	if(!skip) {
		g = $4
		skip = 1
		print
		next
	}
	v = system("awk -f genops.awk -v group=" g)
	if(v) err("genops failed (group "g")")
	skip = 0
}

!skip {
	print
}
