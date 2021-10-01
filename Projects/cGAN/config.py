# Hyperparameters and other global variables
import torch

DEVICE = torch.device( 'cuda' if torch.cuda.is_available() else 'cpu')
LAMBDA = 100

# Data
BATCH_SIZE = 8
NUM_WORKERS = 2
TRAIN_PATH = 'data/cityscapes/train'
TEST_PATH = 'data/cityscapes/val'

# Optimizer
LR = 0.0002
BETA_1 = 0.5
BETA_2 = 0.999

# Training
EPOCHS = 10
GEN_CHECKPOINT = 'gen_checkpoint.pt'
DISC_CHECKPOINT = 'disc_checkpoint.pt'