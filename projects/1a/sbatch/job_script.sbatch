#!/bin/bash

#SBATCH -n 1
#SBATCH --cpus-per-task=1
#SBATCH --time=0:01:00
#SBATCH --job-name="hello_world"
#SBATCH --mem-per-cpu=512
#SBATCH --output="4.out"
#SBATCH --open-mode=truncate
#SBATCH --constraint="EPYC_7763"

module load gcc/6.3.0
cd ../bin
./4
