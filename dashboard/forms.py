from django import forms
from api.models import Task, Note

class TaskForm(forms.ModelForm):
    class Meta:
        model = Task
        fields = ['title', 'description']

class NoteForm(forms.ModelForm):
    class Meta:
        model = Note
        fields = ['task', 'title', 'content', 'file']

    def __init__(self, user, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.fields['task'].queryset = Task.objects.filter(user=user)