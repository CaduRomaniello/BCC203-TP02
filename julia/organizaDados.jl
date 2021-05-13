mutable struct QS
    tempo::String
    comp::String
    escrita::String
    leitura::String
    QS() = new("", "", "", "")
end

mutable struct VC
    tempo::String
    comp::String
    escrita::String
    leitura::String
    VC() = new("", "", "", "")
end

mutable struct SS
    tempo::String
    comp::String
    escrita::String
    leitura::String
    SS() = new("", "", "", "")
end

mutable struct Dados
    quick::Array{QS, 1}
    caminhos::Array{VC, 1}
    selecao::Array{SS, 1}
    Dados() = new([QS(), QS(), QS()], [VC(), VC(), VC()], [SS(), SS(), SS()])
end


function mainOrganiza()

    local ordenacao::Array{Int64, 1} = [1, 2, 3] 
    local quantidade::Array{Int64, 1} = [100, 1000, 10000, 100000, 471705]
    local dados::Array{Dados, 1} = [Dados(), Dados(), Dados(), Dados(), Dados()]
    local counter = 0
    
    for i in quantidade 
        counter += 1
        for j in ordenacao
            
            # Varios caminhos
            open("../dados/variosCaminhos/quantidade-$(i)_ordenacao-$(j).txt", "r") do arq

                texto = read(arq, String)
                texto = split(texto, "\n")
                dados[counter].caminhos[j].tempo   = split(texto[12], ": ")[2]
                dados[counter].caminhos[j].comp    = split(texto[11], ": ")[2]
                dados[counter].caminhos[j].escrita = split(texto[10], ": ")[2]
                dados[counter].caminhos[j].leitura = split(texto[9], ": ")[2]

            end

            # Substituicao selecao
            open("../dados/subSelecao/quantidade-$(i)_ordenacao-$(j).txt", "r") do arq

                texto = read(arq, String)
                texto = split(texto, "\n")

                dados[counter].selecao[j].tempo   = split(texto[12], ": ")[2]
                dados[counter].selecao[j].comp    = split(texto[11], ": ")[2]
                dados[counter].selecao[j].escrita = split(texto[10], ": ")[2]
                dados[counter].selecao[j].leitura = split(texto[9], ": ")[2]

            end

            # Quicksort
            open("../dados/quickSort/quantidade-$(i)_ordenacao-$(j).txt", "r") do arq

                texto = read(arq, String)
                texto = split(texto, "\n")

                dados[counter].quick[j].tempo   = split(texto[12], ": ")[2]
                dados[counter].quick[j].comp    = split(texto[11], ": ")[2]
                dados[counter].quick[j].escrita = split(texto[10], ": ")[2]
                dados[counter].quick[j].leitura = split(texto[9], ": ")[2]

            end

        end

        # Tempo total
        file = open("../dados/graficos/tempo_quantidade-$(i).txt", create = true, write = true)

        write(file, "Quicksort\n")
        for j in ordenacao
            write(file, "Tempo: $(dados[counter].quick[j].tempo)\n")
        end
        
        write(file, "\nSubstituicao Selecao\n")
        for j in ordenacao
            write(file, "Tempo: $(dados[counter].selecao[j].tempo)\n")
        end

        write(file, "\nVarios Caminhos\n")
        for j in ordenacao
            write(file, "Tempo: $(dados[counter].caminhos[j].tempo)\n")
        end

        close(file)

        # Comparacoes
        file = open("../dados/graficos/comp_quantidade-$(i).txt", create = true, write = true)

        write(file, "Quicksort\n")
        for j in ordenacao
            write(file, "Comp: $(dados[counter].quick[j].comp)\n")
        end
        
        write(file, "\nSubstituicao Selecao\n")
        for j in ordenacao
            write(file, "Comp: $(dados[counter].selecao[j].comp)\n")
        end

        write(file, "\nVarios Caminhos\n")
        for j in ordenacao
            write(file, "Comp: $(dados[counter].caminhos[j].comp)\n")
        end

        close(file)

        # Escrita
        file = open("../dados/graficos/escrita_quantidade-$(i).txt", create = true, write = true)

        write(file, "Quicksort\n")
        for j in ordenacao
            write(file, "Escrita: $(dados[counter].quick[j].escrita)\n")
        end
        
        write(file, "\nSubstituicao Selecao\n")
        for j in ordenacao
            write(file, "Escrita: $(dados[counter].selecao[j].escrita)\n")
        end

        write(file, "\nVarios Caminhos\n")
        for j in ordenacao
            write(file, "Escrita: $(dados[counter].caminhos[j].escrita)\n")
        end

        close(file)

        # Leitura
        file = open("../dados/graficos/leitura_quantidade-$(i).txt", create = true, write = true)

        write(file, "Quicksort\n")
        for j in ordenacao
            write(file, "Leitura: $(dados[counter].quick[j].leitura)\n")
        end
        
        write(file, "\nSubstituicao Selecao\n")
        for j in ordenacao
            write(file, "Leitura: $(dados[counter].selecao[j].leitura)\n")
        end

        write(file, "\nVarios Caminhos\n")
        for j in ordenacao
            write(file, "Leitura: $(dados[counter].caminhos[j].leitura)\n")
        end

        close(file)

    end

end

mainOrganiza()