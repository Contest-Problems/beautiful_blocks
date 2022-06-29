g++ ../sol/solution.cpp -o sol1
g++ random_gen.cpp -o gen
g++ ../sol/brute.cpp -o sol2

for((i = 1;; ++i)); do
    echo $i
    ./gen > int
    ./sol1 < int > out1
    ./sol2 < int > out2
    diff -w out1 out2 || break
done

rm sol1
rm sol2
rm gen
