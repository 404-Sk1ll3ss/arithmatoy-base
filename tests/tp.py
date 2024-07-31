# Aucun n'import ne doit être fait dans ce fichier


def nombre_entier(n: int) -> str:
    return 'S' * n + '0'

def S(n: str) -> str:
    return 'S' + n

def addition(a: str, b: str) -> str:
    if a == '0':
        return b
    elif a[0] == 'S':
        return S(addition(a[1:],b))

def multiplication(a: str, b: str) -> str:
    if a == '0':
        return '0'
    return addition(b,multiplication(a[1:],b))

def facto_ite(n: int) -> int:
    fact = 1
    while(n > 0):
        fact*=n
        n-=1
    return fact

def facto_rec(n: int) -> int:
    if(n <= 0):
        return 1
    return facto_ite(n-1) * n

def fibo_rec(n: int) -> int:
    if(n == 0):
        return 0
    if(n == 1):
        return 1
    return fibo_rec(n - 1) + fibo_rec(n - 2)

def fibo_ite(n: int) -> int:

    ls = [0,1]
    if n == 0:
        return ls[0]
    elif n == 1:
        return ls[1]
    else:
        for i in range(1,n):
            ls.append(ls[len(ls) - 1] + ls[len(ls) - 2])
    return ls[n]

def golden_phi(n: int) -> int:
    phi = 1
    for i in range(1,n+1):
        phi = 1 + 1/phi
    return phi

def sqrt5(n: int) -> int:
    if n == 0:
        return 0
    return 1 + sqrt5(n-1) / 2

def pow(a: float, n: int) -> float:
    if n == 0:
        return 1
    return pow(a,n - 1) * a
