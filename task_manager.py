#!/usr/bin/env python3
"""
Task Management CLI Tool
A command-line interface for managing personal tasks with priorities.
"""

import argparse
import json
import os
from datetime import datetime
from typing import List, Dict

TASKS_FILE = "tasks.json"


class TaskManager:
    def __init__(self, tasks_file: str = TASKS_FILE):
        self.tasks_file = tasks_file
        self.tasks = self.load_tasks()

    def load_tasks(self) -> List[Dict]:
        """Load tasks from JSON file."""
        if os.path.exists(self.tasks_file):
            try:
                with open(self.tasks_file, 'r') as f:
                    return json.load(f)
            except json.JSONDecodeError:
                return []
        return []

    def save_tasks(self) -> None:
        """Save tasks to JSON file."""
        with open(self.tasks_file, 'w') as f:
            json.dump(self.tasks, f, indent=2)

    def add_task(self, description: str, priority: str = "medium") -> None:
        """Add a new task with specified priority."""
        task = {
            "id": len(self.tasks) + 1,
            "description": description,
            "priority": priority.lower(),
            "completed": False,
            "created_at": datetime.now().isoformat()
        }
        self.tasks.append(task)
        self.save_tasks()
        print(f"✓ Task added: {description} (Priority: {priority})")

    def list_tasks(self, show_completed: bool = False) -> None:
        """List all tasks, optionally showing completed tasks."""
        if not self.tasks:
            print("No tasks found.")
            return

        priority_order = {"high": 1, "medium": 2, "low": 3}
        sorted_tasks = sorted(self.tasks, key=lambda x: priority_order.get(x["priority"], 4))

        print("\n" + "="*70)
        print("TASKS")
        print("="*70)

        for task in sorted_tasks:
            if not show_completed and task["completed"]:
                continue

            status = "✓" if task["completed"] else "○"
            priority = task["priority"].upper()
            priority_indicator = {
                "HIGH": "🔴",
                "MEDIUM": "🟡",
                "LOW": "🟢"
            }.get(priority, "⚪")

            print(f"\n[{task['id']}] {status} {priority_indicator} {priority}")
            print(f"    {task['description']}")
            if task["completed"]:
                print(f"    Status: Completed")

        print("\n" + "="*70 + "\n")

    def complete_task(self, task_id: int) -> None:
        """Mark a task as completed."""
        for task in self.tasks:
            if task["id"] == task_id:
                task["completed"] = True
                task["completed_at"] = datetime.now().isoformat()
                self.save_tasks()
                print(f"✓ Task {task_id} marked as complete!")
                return
        print(f"✗ Task {task_id} not found.")

    def delete_task(self, task_id: int) -> None:
        """Delete a task by ID."""
        for i, task in enumerate(self.tasks):
            if task["id"] == task_id:
                description = task["description"]
                self.tasks.pop(i)
                self.save_tasks()
                print(f"✓ Task deleted: {description}")
                return
        print(f"✗ Task {task_id} not found.")

    def clear_completed(self) -> None:
        """Remove all completed tasks."""
        original_count = len(self.tasks)
        self.tasks = [task for task in self.tasks if not task["completed"]]
        removed = original_count - len(self.tasks)
        self.save_tasks()
        print(f"✓ Removed {removed} completed task(s).")


def main():
    parser = argparse.ArgumentParser(
        description="Task Management CLI Tool - Manage your tasks efficiently",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s add "Complete project documentation" --priority high
  %(prog)s list
  %(prog)s complete 1
  %(prog)s delete 2
        """
    )

    subparsers = parser.add_subparsers(dest="command", help="Available commands")

    # Add task command
    add_parser = subparsers.add_parser("add", help="Add a new task")
    add_parser.add_argument("description", help="Task description")
    add_parser.add_argument(
        "-p", "--priority",
        choices=["high", "medium", "low"],
        default="medium",
        help="Task priority (default: medium)"
    )

    # List tasks command
    list_parser = subparsers.add_parser("list", help="List all tasks")
    list_parser.add_argument(
        "-a", "--all",
        action="store_true",
        help="Show completed tasks"
    )

    # Complete task command
    complete_parser = subparsers.add_parser("complete", help="Mark task as complete")
    complete_parser.add_argument("task_id", type=int, help="ID of task to complete")

    # Delete task command
    delete_parser = subparsers.add_parser("delete", help="Delete a task")
    delete_parser.add_argument("task_id", type=int, help="ID of task to delete")

    # Clear completed tasks
    subparsers.add_parser("clear", help="Remove all completed tasks")

    args = parser.parse_args()

    if not args.command:
        parser.print_help()
        return

    task_manager = TaskManager()

    if args.command == "add":
        task_manager.add_task(args.description, args.priority)
    elif args.command == "list":
        task_manager.list_tasks(show_completed=args.all)
    elif args.command == "complete":
        task_manager.complete_task(args.task_id)
    elif args.command == "delete":
        task_manager.delete_task(args.task_id)
    elif args.command == "clear":
        task_manager.clear_completed()


if __name__ == "__main__":
    main()
