from django.shortcuts import render, redirect
from django.contrib.auth.decorators import login_required
from api.models import Task, Note
from .forms import TaskForm, NoteForm
from django.shortcuts import get_object_or_404
from django.views.decorators.http import require_POST
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
@login_required
def task_edit_view(request, pk):
    task = get_object_or_404(Task, pk=pk, user=request.user)
    
    if request.method == 'POST':
        form = TaskForm(request.POST, instance=task)
        if form.is_valid():
            form.save()
            return redirect('dashboard')
    else:
        form = TaskForm(instance=task)
        
    return render(request, 'dashboard/edit_task.html', {
        'form': form,
        'task': task
    })


@require_POST
@login_required
def task_delete_view(request, pk):
    task = get_object_or_404(Task, pk=pk, user=request.user)
    task.delete()
    return redirect('dashboard')


@require_POST
@login_required
def task_toggle_complete_view(request, pk):
    task = get_object_or_404(Task, pk=pk, user=request.user)
    task.completed = not task.completed
    task.save()
    return redirect('dashboard')