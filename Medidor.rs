use std::time::Instant;

fn criba_base(limite: usize) -> Vec<usize> {
    let mut es_primo = vec![true; limite + 1];
    let mut primos = vec![];

    es_primo[0] = false;
    es_primo[1] = false;

    for i in 2..=((limite as f64).sqrt() as usize) {
        if es_primo[i] {
            let mut j = i * i;
            while j <= limite {
                es_primo[j] = false;
                j += i;
            }
        }
    }

    for i in 2..=limite {
        if es_primo[i] {
            primos.push(i);
        }
    }

    primos
}

fn contar_primos(n: usize) -> usize {
    let limite = (n as f64).sqrt() as usize;
    let primos_base = criba_base(limite);

    let mut total = primos_base.len();
    let mut inicio = limite;
    let mut fin = inicio + limite;

    while inicio < n {
        if fin > n {
            fin = n;
        }

        let tamaño = fin - inicio + 1;
        let mut es_primo = vec![true; tamaño];

        for &p in &primos_base {
            let mut base = (inicio / p) * p;
            if base < inicio {
                base += p;
            }

            let mut j = base;
            while j <= fin {
                es_primo[j - inicio] = false;
                j += p;
            }
        }

        for i in inicio..=fin {
            if es_primo[i - inicio] {
                total += 1;
            }
        }

        inicio = fin + 1;
        fin = inicio + limite;
    }

    total
}

fn main() {
    let n: usize = 20_000_000;

    let inicio = Instant::now();
    let total = contar_primos(n);
    let duracion = inicio.elapsed();

    println!("Total de primos <= {}: {}", n, total);
    println!("Tiempo: {:.4} segundos", duracion.as_secs_f64());
}
