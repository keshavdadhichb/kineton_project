from django.shortcuts import render, redirect
from django.contrib.auth.decorators import login_required
from api.models import Task, Note
from .forms import TaskForm, NoteForm

@login_required
def dashboard_view(request):
    tasks = Task.objects.filter(user=request.user)
    notes = Note.objects.filter(user=request.user)

    task_form = TaskForm()
    note_form = NoteForm(user=request.user)

    if request.method == 'POST':
        if 'submit_task' in request.POST:
            task_form = TaskForm(request.POST)
            if task_form.is_valid():
                task = task_form.save(commit=False)
                task.user = request.user
                task.save()
                return redirect('dashboard')

        elif 'submit_note' in request.POST:
            note_form = NoteForm(request.user, request.POST, request.FILES)
            if note_form.is_valid():
                note = note_form.save(commit=False)
                note.user = request.user
                note.save()
                return redirect('dashboard')

    context = {
        'tasks': tasks,
        'notes': notes,
        'task_form': task_form,
        'note_form': note_form
    }
    return render(request, 'dashboard/index.html', context)