#!/bin/bash

#SBATCH -n 1
#SBATCH --cpus-per-task=1
#SBATCH --time=0:01:00
#SBATCH --job-name="2_2"
#SBATCH --mem-per-cpu=512
#SBATCH --output="7H12.fig"
#SBATCH --open-mode=truncate
#SBATCH --constraint="EPYC_7H12"

hwloc-ls --whole-system --no-io -f --of fig 7H12.fig
