# Task Management CLI Tool

A command-line interface application built with Python for creating, tracking, and managing personal tasks. Features include adding tasks with priorities, marking tasks as complete, and listing all tasks.

## Features

- ✅ Add tasks with customizable priorities (high, medium, low)
- 📋 List all active tasks
- ✓ Mark tasks as complete
- 🗑️ Delete tasks
- 🧹 Clear all completed tasks
- 💾 Persistent storage using JSON
- 🎨 Color-coded priority indicators

## Technologies

- Python 3.6+
- argparse (standard library)
- JSON for data persistence

## Installation

1. Clone the repository:
```bash
git clone https://github.com/daveno16/task-management-cli.git
cd task-management-cli
```

2. Make the script executable (optional):
```bash
chmod +x task_manager.py
```

## Usage

### Add a new task

```bash
python task_manager.py add "Complete project documentation" --priority high
python task_manager.py add "Review pull requests" -p medium
python task_manager.py add "Update README"
```

### List all tasks

```bash
# Show active tasks only
python task_manager.py list

# Show all tasks including completed
python task_manager.py list --all
```

### Mark a task as complete

```bash
python task_manager.py complete 1
```

### Delete a task

```bash
python task_manager.py delete 2
```

### Clear completed tasks

```bash
python task_manager.py clear
```

### Help

```bash
python task_manager.py --help
python task_manager.py add --help
```

## Examples

```bash
# Add tasks with different priorities
python task_manager.py add "Fix critical bug" --priority high
python task_manager.py add "Write unit tests" --priority medium
python task_manager.py add "Update dependencies" --priority low

# List tasks (sorted by priority)
python task_manager.py list

# Complete a task
python task_manager.py complete 1

# View all tasks including completed ones
python task_manager.py list --all

# Remove all completed tasks
python task_manager.py clear
```

## Task Priority Levels

- 🔴 **HIGH** - Urgent and important tasks
- 🟡 **MEDIUM** - Standard priority tasks (default)
- 🟢 **LOW** - Tasks that can wait

## Data Storage

Tasks are stored in a `tasks.json` file in the same directory as the script. This file is automatically created when you add your first task.

## Requirements

- Python 3.6 or higher
- No external dependencies required

## Project Structure

```
task-management-cli/
├── task_manager.py    # Main application
├── README.md          # Documentation
├── tasks.json         # Task data (auto-generated)
└── .gitignore         # Git ignore file
```

## Contributing

Feel free to fork this project and submit pull requests for any improvements.

## License

Copyright © 2023 David Iyareen Omayo

## Author

David Iyareen Omayo
