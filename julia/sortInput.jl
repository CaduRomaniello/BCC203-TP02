mutable struct Registro
    matricula # 1 a 8
    nota # 0 e 100 - 10 a 14
    estado # 16 e 17
    cidade # 19 a 68
    curso # 70 a 99 
end

function main(ARGS)

    # 1 -> crescente; 2 -> decrescente; 3 -> desordenado
    local file2 = open("../Input/$(ARGS[1])", create = true, write = true, read = true)
    local file = []
    
    open("../Input/PROVAO.txt", "r") do f
        while !eof(f)
            x = readline(f)
            push!(file, Registro(x[1:8], x[10:14], x[16:17], x[19:68], x[70:99]))
        end
    end

    if (parse(Int64, ARGS[2]) == 2)
        sort!(file, rev = true, alg=QuickSort, by = x -> x.nota)
    elseif (parse(Int64, ARGS[2]) == 1)
        sort!(file, rev = false, alg=QuickSort, by = x -> x.nota)
    else
    end

    for i in file
        write(file2, "$(i.matricula) $(i.nota) $(i.estado) $(i.cidade) $(i.curso)\r\n")
    end

    close(file2)

end

main(ARGS)

#=
• número de inscrição do aluno (valor inteiro longo, ocupando as colunas 1 a 8 do arquivo texto);
• nota obtida pelo aluno (valor real entre 0.0 e 100.0, ocupando as colunas 10 a 14 do arquivo texto);
• estado do aluno (cadeia de 2 caracteres, ocupando as colunas 16 e 17 do arquivo texto);
• cidade do aluno (cadeia de 50 caracteres, ocupando as colunas 19 a 68 do arquivo texto);
• curso do aluno (cadeia de 30 caracteres, ocupando as colunas 70 a 99 do arquivo texto). 
=#