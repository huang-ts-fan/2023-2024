# DL_module

This repository and README contains relevant information regarding the Deep Learning module, please read it all carefully. 

The machine learning framework we will use is [PyTorch](https://pytorch.org/).

# Table of contents
1. [Objectives](#objectives)
2. [Course contents](#coursecontents)
3. [Assessments](#assessments)
4. [Primer materials and bibliography](#primer)
5. [Lecture materials](#lectures)
6. [Google Colab](#colab)
7. [Teaching team](#team)
8. [Learning outcomes](#outcomes)


## Objectives <a name="objectives"></a>

The objective of this module is to equip you with a solid foundation to understand the basic principles of deep learning (DL).

Despite the humongous size of the deep-learning research landscape, and the impossibility to cover all the topics it encompasses, this course will provide you with all the fundamental concepts, building blocks, and mathematical methods that are used in the majority of modern complex applications, preparing you to develop your professional careers in this field.

## Course contents <a name="coursecontents"></a>

During the course we will cover the following topics:

1. Introduction to Deep Learning
2. Basic DL concepts (backprop, regularisation, etc).
3. PyTorch primer
4. Feed-forward Networks (FFNs)
5. Convolutional neural networks (CNNs)
6. Probability for DL
7. Generative models:
	- Variational autoencoders (VAEs)
	- Generative adversarial networks (GANs)
	- Diffusion models
8. Recurrent neural networks (RNNs) and long short-term memory networks (LSTMs)
10. Transformers
11. Other DL methods, architectures, and strategies (informative session, **not assessed**):

The contents will be delivered using jupyter notebooks that contain both theory and practical implementations.

Most days will be structured as follows:

| time  | session |
|---------------|-----------------------------------------------------------------------|
| 9:00h-12:00h  | theory and implementation |
| 14:00h-17:00h | exercise session |


with a few exceptions:

- On Wednesday afternoons we will not have any sessions.

- Other dates that will not follow the morning-lecture/afternoon-exercise structure will be:

| session  | activity |
|---------------|-----------------------------------------------------------------------|
| Thursday 7 Dec (afternoon) & Friday 8 Dec (all day) | coursework 1 release and working time |
| Thursday 14 Dec (afternoon) & Friday 15 Dec (all day) | coursework 2 release and working time |
| Thursday 14 Dec (morning) | Q&A and review session before coursework 2 |


## Assessments <a name="assessments"></a>

The module assessment is based on two courseworks.


| **COURSEWORK 1** | **Date and time** |
| :------------------ | :---: |
| *Release* | Thursday 7 Dec 14:00h |
| *Due (deadline)* | Friday 8 Dec 18:00h |


| **COURSEWORK 2** | **Date and time** |
| :------------------ | :---: |
| *Release* | Thursday 14 Dec 14:00h |
| *Due (deadline)* | Friday 15 Dec 18:00h |


## Primer materials and bibliography <a name="primer"></a>

It is NOT mandatory to read (or view) any of the materials in this section.

### Introductory videos

To help prepare for the course, it is recommended to watch these four short (15-20 mins) videos which provide a good introduction to Machine Learning:

1. [But what is a Neural Network? | Deep learning, chapter 1](https://www.youtube.com/watch?v=aircAruvnKk)  
2. [Gradient descent, how neural networks learn | Deep learning, chapter 2](https://www.youtube.com/watch?v=IHZwWFHWa-w&t=11s)   
3. [What is backpropagation really doing? | Deep learning, chapter 3](https://www.youtube.com/watch?v=Ilg3gGewQ5U)  
4. [Backpropagation calculus | Deep learning, chapter 4](https://www.youtube.com/watch?v=tIeHLnjs5U8)  

Probability introductory videos:

1. [Binomial distribution](https://www.youtube.com/watch?v=8idr1WZ1A7Q&list=RDCMUCYO_jab_esuFRV4b17AJtAw&index=2)
2. [Normal distribution](https://www.khanacademy.org/math/statistics-probability/modeling-distributions-of-data/more-on-normal-distributions/v/introduction-to-the-normal-distribution) 
3. [Bayes theorem](https://www.youtube.com/watch?v=HZGCoVF3YvM) 


### Bibliography
- [Pattern recognition and Deep Learning (Christopher M. Bishop)](http://users.isr.ist.utl.pt/~wurmd/Livros/school/Bishop%20-%20Pattern%20Recognition%20And%20Machine%20Learning%20-%20Springer%20%202006.pdf)
- [Deep Learning (Ian Goodfellow, Yoshua Bengio, Aaron Courville)](https://www.deeplearningbook.org/)



## Lecture materials <a name="lectures"></a>

The table below contains the course materials and their scheduled dates. Lecture slides/notebooks will be released on the morning before the start of the lectures. Two notebooks will be provided for each session (morning or afternoon):

- **Codealong**/**Exercises notebook**: Template with some code provided and empty blocks to work on the implementation during the lecture (**Practical**) or during the afternoon exercises (**Exercise**).
- **Solutions notebook**: Practical/Exercise notebook completed with model solutions for the tasks done during the lecture or to be completed during the afternoon exercises.

We encourage you to work on the **Practical/Exercise notebook** and try to implement the tasks proposed during the lectures, but at the same time we want to provide the delivery of the module contents in a complete format to accomodate different learning styles. In particular, some people prefer to focus their attention on the lecture before attempting to implement code themselves, and this is why we provide solutions beforehand.

*\[The numbers in the table (01:, 02:, etc), notebook names, Teams' meetings, and other materials, corresponds to the day of the course (from 01 to 15).\]*


| Session   |   Date <br> Time | Lecture/Exercises | Solutions     |
|-----------|:-------------------|-----------------------|----------------------------|
| Day01 morning - **Intro, Colab, and FFNs**     |   Nov 28 <br> 09:00-12:00  |  [lecture](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day01-Intro_DL_FFNs_and_Colab/Day01_Intro_Colab_and_FFNs_morning.ipynb) <br> [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day01-Intro_DL_FFNs_and_Colab/Day01_Intro_Colab_and_FFNs_morning.ipynb)                     |            | 
| Day01 afternoon - **Intro, Colab, and FFNs**   |   Nov 28 <br> 14:00-17:00  |  [exercises](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day01-Intro_DL_FFNs_and_Colab/Day01_Intro_Colab_and_FFNs_afternoon_exercises.ipynb) <br> [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day01-Intro_DL_FFNs_and_Colab/Day01_Intro_Colab_and_FFNs_afternoon_exercises.ipynb)                     | [solutions](ese-msc-2023/DL_module_2023/blob/main/Day01-Intro_DL_FFNs_and_Colab/Day01_Intro_Colab_and_FFNs_afternoon_solutions.ipynb) <br> [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day01-Intro_DL_FFNs_and_Colab/Day01_Intro_Colab_and_FFNs_afternoon_solutions.ipynb)| 
| Day02 morning - **DL_concepts**   |   Nov 29 <br> 09:00-12:00  |  [lecture](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day02-DL_concepts/Day02-DL_concepts_morning_codealong.ipynb) <br> [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day02-DL_concepts/Day02-DL_concepts_morning_codealong.ipynb)                     | [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day02-DL_concepts/Day02-DL_concepts_morning_solutions.ipynb) <br> [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day02-DL_concepts/Day02-DL_concepts_morning_solutions.ipynb)| 
| Day02 afternoon - **DL_concepts (additional material)**   |   Nov 29 <br> not taught  |  [exercises](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day02-DL_concepts/Day02-DL_concepts_afternoon_exercises.ipynb) <br> [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day02-DL_concepts/Day02-DL_concepts_afternoon_exercises.ipynb)                     | [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day02-DL_concepts/Day02-DL_concepts_afternoon_solutions.ipynb) <br> [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day02-DL_concepts/Day02-DL_concepts_afternoon_solutions.ipynb)| 
| Day 03 morning - **PyTorch**     |   Nov 30 <br> 09:00-12:00  |    [lecture](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day03-PyTorch/Day03-Intro_to_Pytorch_morning_codealong.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day03-PyTorch/Day03-Intro_to_Pytorch_morning_codealong.ipynb)   |      [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day03-PyTorch/Day03-Intro_to_Pytorch_morning_solutions.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day03-PyTorch/Day03-Intro_to_Pytorch_morning_solutions.ipynb)    | 
| Day 03 afternoon - **PyTorch**   |   Nov 30 <br> 14:00-17:00  |  [exercises](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day03-PyTorch/Day03-Intro_to_Pytorch_afternoon_exercises.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day03-PyTorch/Day03-Intro_to_Pytorch_afternoon_exercises.ipynb)   |      [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day03-PyTorch/Day03-Intro_to_Pytorch_afternoon_solutions.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day03-PyTorch/Day03-Intro_to_Pytorch_afternoon_solutions.ipynb)      | 
| Day04 morning - **CNNs part1**    |   Dec 1 <br> 09:00-12:00  |    [lecture](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day04-CNNs_part1/Day04-CNNs_part1_morning_codealong.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day04-CNNs_part1/Day04-CNNs_part1_morning_codealong.ipynb)   |      [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day04-CNNs_part1/Day04-CNNs_part1_morning_solutions.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day04-CNNs_part1/Day04-CNNs_part1_morning_solutions.ipynb)     | 
| Day04 afternoon - **CNNs part1**  |   Dec 1 <br> 14:00-17:00  |   [exercises](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day04-CNNs_part1/Day04-CNNs_part1_afternoon_exercises.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day04-CNNs_part1/Day04-CNNs_part1_afternoon_exercises.ipynb)   |      [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day04-CNNs_part1/Day04-CNNs_part1_afternoon_solutions.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day04-CNNs_part1/Day04-CNNs_part1_afternoon_solutions.ipynb)     | 
| Day05 morning - **CNNs part2**    |   Dec 4 <br> 09:00-12:00  |     [lecture](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day05-CNNs_part2/Day05-CNNs_part2_morning.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day05-CNNs_part2/Day05-CNNs_part2_morning.ipynb)   <hr/>  [Probability](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day05-CNNs_part2/Day05-CNNs_part2_Probability.pdf)  |            | 
| Day05 afternoon - **CNNs part2**  |   Dec 4 <br> 14:00-17:00  |     [exercises](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day05-CNNs_part2/Day05-CNNs_part2_afternoon_exercises.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day05-CNNs_part2/Day05-CNNs_part2_afternoon_exercises.ipynb)   |      [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day05-CNNs_part2/Day05-CNNs_part2_afternoon_solutions.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day05-CNNs_part2/Day05-CNNs_part2_afternoon_solutions.ipynb)       |
| Day06 morning - **VAEs**    |   Dec 5 <br> 09:00-12:00  |      [lecture](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day06-VAEs/Day06-VAEs_morning_Exercise.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day06-VAEs/Day06-VAEs_morning_Exercise.ipynb)   <hr/>  [theory VAEs](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day06-VAEs/Day06-VAEs_theory_lecture.pdf)         |    [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day06-VAEs/Day06-VAEs_morning_Solution.ipynb)  <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day06-VAEs/Day06-VAEs_morning_Solution.ipynb)  | 
| Day06 afternoon - **VAEs**    |   Dec 5 <br> 14:00-17:00  |    [exercises](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day06-VAEs/Day06-VAEs_afternoon_Exercise.ipynb)     <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day06-VAEs/Day06-VAEs_afternoon_Exercise.ipynb)     |        [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day06-VAEs/Day06-VAEs_afternoon_Solution.ipynb)  <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day06-VAEs/Day06-VAEs_afternoon_Solution.ipynb)  |
| Day07 morning - **GANs**    |   Dec 6 <br> 09:00-12:00  |       [lecture](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_morning_codealong.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_morning_codealong.ipynb)      |   [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_morning_solutions.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_morning_solutions.ipynb)   |
| Day07 afternoon - **GANs (additional material)**   | Dec 6 <br> not taught |  [exercise_cGAN](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_conditionalGAN_exercise.ipynb)  <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_conditionalGAN_exercise.ipynb)  <hr/>  [exercise_WGAN](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_WGAN_GP_exercise.ipynb)  <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_WGAN_GP_exercise.ipynb) |  [solution_cGAN](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_conditionalGAN_solution.ipynb)  <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_conditionalGAN_solution.ipynb)   <hr/>  [solution_WGAN](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_WGAN_GP_solution.ipynb)  <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day07-GANs/Day07-GANs_WGAN_GP_solution.ipynb) | 
| Day08 morning - **recap, Q&A**    |   Dec 7 <br> 09:00-12:00  |      <hr>       |   <hr>     |
| Day08 afternoon - **release CW1**    |   Dec 7 <br> 14:00  |       <hr>       |   <hr>       |
| Day09 all day - **CW1**    |   Dec 8 <br> ***deadline 18:00h***  |    <hr>       |   <hr>     |
| Day10 morning - **Diffusion models**    |  Dec 11 <br> 09:00-12:00  |   [lecture](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day10-Diffusion_models/Day10-Diffusion_models_morning_codealong.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day10-Diffusion_models/Day10-Diffusion_models_morning_codealong.ipynb)      |   [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day10-Diffusion_models/Day10-Diffusion_models_morning_solutions.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day10-Diffusion_models/Day10-Diffusion_models_morning_solutions.ipynb)       | 
| Day10 afternoon - **Diffusion models**    |   Dec 11 <br> 09:00-12:00  |  [exercises](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day10-Diffusion_models/Day10-Diffusion_models_afternoon_exercises.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day10-Diffusion_models/Day10-Diffusion_models_afternoon_exercises.ipynb)      |   [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day10-Diffusion_models/Day10-Diffusion_models_afternoon_solutions.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day10-Diffusion_models/Day10-Diffusion_models_afternoon_solutions.ipynb)          |
| Day11 morning - **RNNs & LSTMs**    |   Dec 12 <br> 09:00-12:00  |   [lecture/exercises](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day11-RNNs_and_LSTMs/Day11-RNNs_and_LSTMs_codealong_exercises.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day11-RNNs_and_LSTMs/Day11-RNNs_and_LSTMs_codealong_exercises.ipynb)    <hr/>  [slides](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day11-RNNs_and_LSTMs/Day11-RNNs_and_LSTMs_slides.pdf) |   [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day11-RNNs_and_LSTMs/Day11-RNNs_and_LSTMs_solutions.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day11-RNNs_and_LSTMs/Day11-RNNs_and_LSTMs_solutions.ipynb)          | 
| Day11 afternoon - **RNNs & LSTMs**    |   Dec 12 <br> 14:00-17:00  |    use morning notebook   | use morning notebook       |
| Day12 morning - **Transformer & other DL methods**  |   Dec 13 <br> 09:00-12:00  |     [lecture](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day12-Transformer_and_others/Day12-Transformers_and_other_architectures.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day12-Transformer_and_others/Day12-Transformers_and_other_architectures.ipynb)    |   <hr>  |
| Day12 afternoon - **RL (additional material)** |  Dec 13 <br> not taught | [codealong](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day12-Transformer_and_others/Day12-Deep_RL_additional_codealong.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day12-Transformer_and_others/Day12-Deep_RL_additional_codealong.ipynb) | [solutions](https://github.com/ese-msc-2023/DL_module_2023/blob/main/Day12-Transformer_and_others/Day12-Deep_RL_additional_solutions.ipynb) <br>  [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](http://colab.research.google.com/github/ese-msc-2023/DL_module_2023/blob/main/Day12-Transformer_and_others/Day12-Deep_RL_additional_solutions.ipynb) |
| Day13 morning - **recap, Q&a**    |   Dec 14 <br> 09:00-12:00  |   <hr>          |     <hr>   |
| Day13 afternoon - **release CW1**    |   Dec 14 <br> 14:00  |      <hr>          |     <hr>      |
| Day14 all day - **CW1**    |   Dec 15 <br> ***deadline 18:00h***  |     <hr>     |     <hr>        |



###### The links in the table will become active as we progress during the course.

## Google Colab <a name="colab"></a>

All the coding will be done using Google Colab. It is also possible to use your own computer and run the jupyter notebooks locally, if you prefer, but limited support will be available to help you set up your local system.

There will be an introductory session on how to use Google Colab on Day 01 (27 Nov). We will also provide a Google Colab Pro licence for each of you on Day 08 (6 Dec), for that we will have a live session during class to set up the Colab Pro with provided virtual credit cards.

#### **Do not buy any Colab Pro license as they will provided in class**

#### **A new google account will be created on the first day of the module, which will be a dedicated account for the course. Do NOT use your existing google account for this because the payment system provided could be extended to any personal payment details you have in your personal account**

## Teaching team <a name="team"></a>


- Lluis Guasch [(email)](mailto:lguasch@imperial.ac.uk) - ***module coordinator***
- Raul Adriaensen
- Oscar Bates
- Carlos Cueto
- Jack Ma
- Debbie Pelacani Cruz
- George Strong
- Kun Wang
- Hongcheng Xie
- Di Xu
- Weilin Zhang



## Learning outcomes <a name="outcomes"></a>

#### Over the next three weeks, you will be able to go from here:


<img src="https://imgs.xkcd.com/comics/machine_learning.png" alt="drawing" width="300"/> <br>
[XKCD 1838](https://xkcd.com/1838/)

#### to understanding complex network architectures, how and why they work, and when to use them:

<img src="https://miro.medium.com/max/407/1*o0pS0LbXVw7i41vSISrw1A.png" alt="drawing" width="300"/> <br>
[Transformers](https://arxiv.org/pdf/1706.03762.pdf)








