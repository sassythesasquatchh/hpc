#!/bin/bash

#SBATCH -N 2
#SBATCH -n 2
#SBATCH --cpus-per-task=1
#SBATCH --time=0:01:00
#SBATCH --job-name="hello_world"
#SBATCH --mem-per-cpu=512
#SBATCH --constraint="EPYC_7763"
#SBATCH --output="5.out"
#SBATCH --open-mode=truncate

module load gcc/6.3.0
cd ../bin
srun -N 1 -n 1 --exclusive ./4 &
srun -N 1 -n 1 --exclusive ./4 &
wait
