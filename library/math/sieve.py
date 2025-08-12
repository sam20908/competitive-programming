import array
N_SIEVE = 10**6
spd = array.array("i", range(N_SIEVE + 1))
primes = array.array("i")
for i in range(2, N_SIEVE + 1):
    if spd[i] == i:
        primes.append(i)
    for j in range(len(primes)):
        if i * primes[j] > N_SIEVE:
            break
        spd[i * primes[j]] = primes[j]
        if i % primes[j] == 0:
            break
