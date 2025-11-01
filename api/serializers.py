from rest_framework import serializers
from .models import Task, Note

class TaskSerializer(serializers.ModelSerializer):
    class Meta:
        model = Task
        fields = ['id', 'title', 'description', 'completed', 'created_at', 'updated_at']
        read_only_fields = ['id', 'created_at', 'updated_at']

class NoteSerializer(serializers.ModelSerializer):
    class Meta:
        model = Note
        fields = ['id', 'task', 'title', 'content', 'file', 'created_at', 'updated_at']
        read_only_fields = ['id', 'created_at', 'updated_at']