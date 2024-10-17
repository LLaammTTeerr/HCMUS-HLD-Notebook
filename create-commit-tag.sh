#!/bin/bash

# Navigate to repository (if not already there)
cd /path/to/your/repository || exit

# Get commit count
COMMIT_COUNT=$(git rev-list --count HEAD)

# Define tag name
TAG_NAME="commit-$COMMIT_COUNT"

# Create annotated tag
git tag -a "$TAG_NAME" -m "Tagging commit number $COMMIT_COUNT"

# Push tag to remote
git push origin "$TAG_NAME"

echo "Created and pushed tag $TAG_NAME"
